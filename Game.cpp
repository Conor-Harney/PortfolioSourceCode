#include "stdafx.h"
#include "Game.h"

Game::Game(const sf::Vector2f* SCREENDIMENTIONS, bool* p_gameRestarter): 
	m_GameState(new EnumStore::GAME_STATE(EnumStore::GAME_STATE::NAMEWRITTER)),
	SCREEN_DIMENTIONS(SCREENDIMENTIONS), 
	m_LevelManager(new LevelManager(SCREENDIMENTIONS))
{
	m_name = "";
	m_gameRestarter = p_gameRestarter;
	GlobalConstantsStore::getInsatnce()->init(*SCREENDIMENTIONS);
	m_Camera = new Camera(SCREEN_DIMENTIONS);
	m_inventory = new Inventory(SCREEN_DIMENTIONS, m_GameState, m_Camera);
	player =(new Player(m_LevelManager, *SCREENDIMENTIONS));
	m_messanger = (new Messanger(SCREENDIMENTIONS, m_Camera->getSizeMultiplier(), m_Camera->getPosition()));
	m_EnviermentItemManager = EnvirementItemManager(player, m_messanger, m_LevelManager, m_GameState, m_inventory);
	levelLoaded = new bool(true);
	player->setBlockPos(sf::Vector2u(0,9));
	m_lighting.loadMedia();
	switch1 = new FlipSwitch(sf::Vector2f(0,0), 1);
	//ScoreBoard::getInstance()->sortTopScoresWithoutCurrent();
	m_previousGameState = *m_GameState;
	myInformation = PlayerInformationSet(0,"",0);
	AudioManager::getInstance()->setMusicVolume(50);
	AudioManager::getInstance()->setSfxVolume(20);
}


Game::~Game(void)
{
}

void Game::update(sf::Time timeElapsed){
	bool testBool = true;
	if(*m_GameState == EnumStore::GAME_STATE::IN_GAME){
		if(Controller::getInstance()->actionZoomOut()){
			m_Camera->jumpToZoom(0, sf::Vector2f(0,0));
			m_Camera->setUpSlowZoom(60, player->getPosition(), 1);
		}
		m_Camera->update(player->getPosition(), timeElapsed);
		m_inventory->update();
		
		player->update(timeElapsed);
		m_lighting.update(player->getPosition(), player->getSize());
		sf::Joystick::update();
		m_messanger->update(timeElapsed, m_GameState);
		AudioManager::getInstance()->updateRequests();
		m_EnviermentItemManager.update(timeElapsed);
		
		if(m_LevelManager->getLevelSet() > m_currentLevel){
			m_Camera->jumpToZoom(0 , sf::Vector2f(0,0));
			m_Camera->setUpSlowZoom(60, player->getPosition(), 4);
			m_LevelManager->buildTiledLevel(1);
		}
		m_currentLevel = m_LevelManager->getLevelSet();
		ScoreManager::getInstance()->updateTime(timeElapsed);
		m_messanger->updateClock(ScoreManager::getInstance()->getCurrentLevelTime());
		if(Controller::getInstance()->actionMenu())
		{
			m_Camera->jumpToZoom(0, sf::Vector2f(0,0));
			*m_GameState = EnumStore::GAME_STATE::IN_PAUSE_MENU;
		}
		handleCommands();
	}
	else if(*m_GameState == EnumStore::GAME_STATE::IN_INVENTORY){
		m_inventory->update();
		m_messanger->update(timeElapsed, m_GameState);
	}
	else if(*m_GameState == EnumStore::GAME_STATE::IN_MAIN_MENU || *m_GameState == EnumStore::GAME_STATE::IN_PAUSE_MENU || *m_GameState == EnumStore::GAME_STATE::NAMEWRITTER){
		MenuManager::getInstance()->inMenuUpdate();
		MenuManager::menuOptions currentCall = MenuManager::getInstance()->getOptionCall();
		if(currentCall == MenuManager::menuOptions::NewGame)
		{
			startNewGame();
		}
		else if(currentCall == MenuManager::menuOptions::ScoreBoard)
		{
			*m_GameState = EnumStore::GAME_STATE::SCOREBOARD;
		}
		else if(currentCall == MenuManager::menuOptions::Tutorial)
		{
			*m_GameState = EnumStore::GAME_STATE::TUTORIAL;
		}
		else if(currentCall == MenuManager::menuOptions::Mute)
		{
			AudioManager::getInstance()->toggleMute();
		}
		else if(currentCall == MenuManager::menuOptions::Continue)
		{
			m_Camera->toggleSnapZoom();
			*m_GameState = EnumStore::GAME_STATE::IN_GAME;
		}
		else if(currentCall == MenuManager::menuOptions::AcceptName)
		{
			m_name = EnterNameScreen::getInstance()->acceptSelection();
			*m_GameState = EnumStore::GAME_STATE::IN_MAIN_MENU;
		}
	}
	else if(*m_GameState == EnumStore::GAME_STATE::LOADING){
		if(*levelLoaded){
			//detachLevelLoadingThread();
			*m_GameState = EnumStore::GAME_STATE::IN_GAME;
		}
		else{
			cout << "waiting" << endl;
		}
	}
	MenuManager::getInstance()->updateState(*m_GameState);
	if(*m_GameState == EnumStore::GAME_STATE::SCOREBOARD)
	{
		if(m_previousGameState == EnumStore::GAME_STATE::IN_GAME)
		{//finished game
			m_Camera->jumpToZoom(0, sf::Vector2f(0,0));
			myInformation.setScore(ScoreManager::getInstance()->getTotalScore());
			//ScoreBoard::getInstance()->setMyScore(myInformation);
			m_inventory->clearInventory();
		}
		//if(Controller::getInstance()->actionAction() || Controller::getInstance()->actionMenuSelect() || Controller::getInstance()->actionMenu())
		if(Controller::getInstance()->actionMenu())
		{
			*m_GameState = EnumStore::GAME_STATE::IN_MAIN_MENU;
			AudioManager::getInstance()->stopMusic();
		}
	}
	if(*m_GameState == EnumStore::GAME_STATE::TUTORIAL)
	{
		if(Controller::getInstance()->actionMenu())
		{
			*m_GameState = EnumStore::GAME_STATE::IN_MAIN_MENU;
		}
	}
	if(m_previousGameState == EnumStore::GAME_STATE::IN_MAIN_MENU && *m_GameState == EnumStore::GAME_STATE::IN_GAME)
	{
		*m_gameRestarter = true;
	}
	m_previousGameState = *m_GameState;
	
}

void Game::togLevel()
{
	noThreadLevLoaded = false;
	if(m_LevelManager->getCurrentRoom() == 1)
	{
		levelLoadThreadFunc(2);
	}
	else
	{
		levelLoadThreadFunc(1);
	}
}

void Game::draw(sf::RenderWindow* window){

	window->setView(m_Camera->getView());

	m_LevelManager->drawAllTiles(window);
	
	m_EnviermentItemManager.render(window);
	player->draw(window);
	m_lighting.render(window);
	
	//switch1->render(window);
	if(*m_GameState == EnumStore::GAME_STATE::IN_INVENTORY){
		m_inventory->draw(window);
	}
	m_messanger->Draw(window);	
	MenuManager::getInstance()->render();
	if(*m_GameState == EnumStore::GAME_STATE::SCOREBOARD){
		//ScoreBoard::getInstance()->renderScoreboard();
	}
	window->setView(window->getDefaultView());
}

void Game::handleCommands(){
	if(Controller::getInstance()->actionLevelLeft()){
		if(!m_inventory->isActive()){
			noThreadLevLoaded = false;
			levelLoadThreadFunc(1);
		}
	}
	if(Controller::getInstance()->actionLevelRight()){
		if(!m_inventory->isActive()){
			noThreadLevLoaded = false;
			levelLoadThreadFunc(2);
		}
	}
	if(Controller::getInstance()->actionToggleLevel()){
		if(!m_inventory->isActive()){
			noThreadLevLoaded = false;
			if(m_LevelManager->getCurrentRoom() == 1)
			{
				levelLoadThreadFunc(2);
			}
			else
			{
				levelLoadThreadFunc(1);
			}
		}
	}
}

void Game::loadNewLevel(int levelNum){
	loadLevelThread = thread(&Game::levelLoadThreadFunc,this,levelNum);
	loadLevelThread.detach();
}

void Game::levelLoadThreadFunc(int levelNum){
	string message = "level " + std::to_string(levelNum);
	m_messanger->displayMessage(message);
	*m_GameState = EnumStore::GAME_STATE::LOADING;
	*levelLoaded = false;
	m_LevelManager->buildTiledLevel(levelNum, levelLoaded);
}

void Game::detachLevelLoadingThread(){
	loadLevelThread.~thread();
}

sf::Vector2f Game::itemToCenterOfBlock(sf::Vector2u gridPos){
	sf::Vector2f retPos = sf::Vector2f(
		(gridPos.x * m_LevelManager->SCREEN_CELL_SIZE.x) + (m_LevelManager->SCREEN_CELL_SIZE.x / 2), 
		(gridPos.y * m_LevelManager->SCREEN_CELL_SIZE.y) + (m_LevelManager->SCREEN_CELL_SIZE.y / 2));
	return retPos;
}

void Game::startNewGame()
{
	m_LevelManager->setLevelSet(0);
	ScoreManager::getInstance()->clearScore();
	myInformation = PlayerInformationSet(0,m_name,0);
	m_Camera->jumpToZoom(0,sf::Vector2f(0,0));
	player->setBlockPos(sf::Vector2u(0,9));
	m_LevelManager->buildTiledLevel(1);
	m_EnviermentItemManager.loadLevelItems(0, 0);
	AudioManager::getInstance()->setMusicVolume(50);
	AudioManager::getInstance()->playMusic(1);
	AudioManager::getInstance()->setSfxVolume(20);
	noThreadLevLoaded = true;
	m_currentLevel = 0;
	m_Camera->toggleZoom(2);
	*m_GameState = EnumStore::GAME_STATE::IN_GAME;
}