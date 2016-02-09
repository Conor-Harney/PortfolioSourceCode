#include "stdafx.h"
#include "MenuManager.h"

MenuManager* MenuManager::m_instance;

MenuManager* MenuManager::getInstance()
{
	if(m_instance == 0)
	{
		m_instance = new MenuManager();
	}
	return m_instance;
}

void MenuManager::inMenuUpdate()
{
	if(Controller::getInstance()->actionDownOnce())
	{
		nextButtonDown();
		AudioManager::getInstance()->playSoundEffect("click1");
	}
	else if(Controller::getInstance()->actionUpOnce()){
		nextButtonUp();
		AudioManager::getInstance()->playSoundEffect("click1");
	}
	else if(Controller::getInstance()->actionMenuSelect())
	{
		m_optionSellected = true;
		AudioManager::getInstance()->playSoundEffect("click1");
	}
	else
	{
		m_optionSellected = false;
	}
	if (m_currentGameState == EnumStore::GAME_STATE::NAMEWRITTER)
	{
		EnterNameScreen::getInstance()->update();
	}
}

void MenuManager::render()
{
	if(m_currentGameState == EnumStore::GAME_STATE::IN_PAUSE_MENU)
	{
		ResourceManager::getInstance()->getRenderer()->draw(*m_menuBackground);
		ResourceManager::getInstance()->getRenderer()->draw(*m_continueButton);
		ResourceManager::getInstance()->getRenderer()->draw(*m_muteButton);
		ResourceManager::getInstance()->getRenderer()->draw(*m_buttonHighlighte);
	}
	else if(m_currentGameState == EnumStore::GAME_STATE::IN_MAIN_MENU)
	{
		ResourceManager::getInstance()->getRenderer()->draw(*m_menuBackground);
		ResourceManager::getInstance()->getRenderer()->draw(*m_newGameButton);
		ResourceManager::getInstance()->getRenderer()->draw(*m_scoreboardButton);
		ResourceManager::getInstance()->getRenderer()->draw(*m_tutorialButton);
		ResourceManager::getInstance()->getRenderer()->draw(*m_buttonHighlighte);
	}
	else if(m_currentGameState == EnumStore::GAME_STATE::SCOREBOARD)
	{

	}
	else if(m_currentGameState == EnumStore::GAME_STATE::TUTORIAL)
	{
		ResourceManager::getInstance()->getRenderer()->draw(*m_menuBackground);
		ResourceManager::getInstance()->getRenderer()->draw(*m_tutorialScreen);
	}
	else if (m_currentGameState == EnumStore::GAME_STATE::NAMEWRITTER)
	{
		EnterNameScreen::getInstance()->render();
	}
	else
	{
		//ResourceManager::getInstance()->getRenderer()->draw(*m_menuBackground);
		//ResourceManager::getInstance()->getRenderer()->draw(*m_continueButton);
		//ResourceManager::getInstance()->getRenderer()->draw(*m_muteButton);
	}
}

MenuManager::MenuManager(void)
{
	m_optionSellected = false;
	m_currentButton = 1;
	buttonsInCurrentMenu = 3;
	m_buttonSize = sf::Vector2f(150,50);
	buttonXPos = (GlobalConstantsStore::getInsatnce()->getScreenDimensions().x / 2) - (m_buttonSize.x / 2);
	buttonYPoss[0]= 100;
	buttonYPoss[1]= 300;
	buttonYPoss[2]= 500;
	m_menuBackground = new sf::Sprite();
	ResourceManager::getInstance()->setUpSprite(m_menuBackground, "menuBackground", GlobalConstantsStore::getInsatnce()->getScreenDimensions());
	
	m_newGameButton = new sf::Sprite();
	ResourceManager::getInstance()->setUpSprite(m_newGameButton, "newGameButton", m_buttonSize);
	m_newGameButton->setPosition(buttonXPos, buttonYPoss[0]);

	m_scoreboardButton = new sf::Sprite();
	ResourceManager::getInstance()->setUpSprite(m_scoreboardButton, "scoreboardButton", m_buttonSize);
	m_scoreboardButton->setPosition(buttonXPos, buttonYPoss[1]);
	
	m_continueButton = new sf::Sprite();
	ResourceManager::getInstance()->setUpSprite(m_continueButton, "continueButton", m_buttonSize);
	m_continueButton->setPosition(buttonXPos, buttonYPoss[0]);
	
	m_muteButton = new sf::Sprite();
	ResourceManager::getInstance()->setUpSprite(m_muteButton, "muteButton", m_buttonSize);
	m_muteButton->setPosition(buttonXPos, buttonYPoss[1]);

	m_tutorialButton = new sf::Sprite();
	ResourceManager::getInstance()->setUpSprite(m_tutorialButton, "tutorialButton", m_buttonSize);
	m_tutorialButton->setPosition(buttonXPos, buttonYPoss[2]);

	m_buttonHighlighte = new sf::Sprite();
	ResourceManager::getInstance()->setUpSprite(m_buttonHighlighte, "buttonHighlite", m_buttonSize);
	m_buttonHighlighte->setPosition(buttonXPos, buttonYPoss[0]);

	m_tutorialScreen = new sf::Sprite();
	ResourceManager::getInstance()->setUpSprite(m_tutorialScreen, "tutorialImage", GlobalConstantsStore::getInsatnce()->getScreenDimensions());
	m_tutorialScreen->setPosition(0,0);

}

MenuManager::~MenuManager(void)
{
}

void MenuManager::updateState(EnumStore::GAME_STATE p_gameState)
{
	if(p_gameState != m_currentGameState)
	{
		m_buttonHighlighte->setPosition(buttonXPos, buttonYPoss[0]);
		m_currentButton = 1;
		m_currentGameState = p_gameState;
		if(m_currentGameState == EnumStore::GAME_STATE::IN_MAIN_MENU)
		{
			AudioManager::getInstance()->playSoundEffect("click1");
			buttonsInCurrentMenu = 3;
		}
		else if(m_currentGameState == EnumStore::GAME_STATE::IN_PAUSE_MENU)
		{
			AudioManager::getInstance()->playSoundEffect("click1");
			buttonsInCurrentMenu = 2;
		}
	}
}

void MenuManager::nextButtonDown()
{
	m_currentButton ++;
	if(m_currentButton > buttonsInCurrentMenu)
	{
		m_currentButton = 1;
	}
	m_buttonHighlighte->setPosition(buttonXPos, buttonYPoss[m_currentButton - 1]);
}
	
void MenuManager::nextButtonUp()
{
	m_currentButton --;
	if(m_currentButton < 1)
	{
		m_currentButton = buttonsInCurrentMenu;
	}
	m_buttonHighlighte->setPosition(buttonXPos, buttonYPoss[m_currentButton - 1]);
}

MenuManager::menuOptions MenuManager::getOptionCall()
{
	menuOptions retOption = None;
	if(m_optionSellected)
	{
		m_optionSellected = false;
		if(m_currentGameState == EnumStore::GAME_STATE::IN_MAIN_MENU)
		{
			if(m_currentButton == 1)
			{
				retOption = NewGame;
			}
			else if(m_currentButton == 2)
			{
				retOption = ScoreBoard;
			}
			else if(m_currentButton == 3)
			{
				retOption = Tutorial;
			}
		}
		else if(m_currentGameState == EnumStore::GAME_STATE::IN_PAUSE_MENU)
		{
			if(m_currentButton == 1)
			{
				retOption = Continue;
			}
			else if(m_currentButton == 2)
			{
				retOption = Mute;
			}
		}
		else if(m_currentGameState == EnumStore::GAME_STATE::NAMEWRITTER)
		{
			retOption = AcceptName;
		}
	}
	return retOption;
}