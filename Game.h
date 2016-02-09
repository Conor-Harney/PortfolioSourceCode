#pragma once
#include "EnumStore.h"
#include <vector>
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include "ResourceManager.h"
#include <string>
#include "Player.h"
#include "LevelManager.h"
#include "Lighting.h"
#include "FlipSwitch.h"
#include "Controller.h"
#include <iostream>
#include "TinyXML2.h"
#include "MapLoader.h"
#include "AudioManager.h"
#include "Messanger.h"
#include "Inventory.h"
#include <future>
#include <thread>
#include <chrono>
#include "Pickup.h"
#include "EnvirementFixture.h"
#include "EnvirementItemManager.h"
#include "Camera.h"
#include "ScoreManager.h"
#include "MenuManager.h"
#include "GlobalConstantsStore.h"
#include "ScoreBoard.h"

using namespace tinyxml2;

class Game
{
public:
	Game(const sf::Vector2f* SCREENDIMENTIONS, bool* p_gameRestarter);
	~Game(void);
	void update(sf::Time timeElapsed);
	void draw(sf::RenderWindow* window);

private:
	const sf::Vector2f* SCREEN_DIMENTIONS;
	Player* player;
	LevelManager *m_LevelManager;
	Lighting m_lighting;
	FlipSwitch* switch1;
	MapLoader m_mapLoader;
	Messanger* m_messanger;
	Inventory* m_inventory;
	EnumStore::GAME_STATE* m_GameState;
	EnumStore::GAME_STATE m_previousGameState;
	void togLevel();
	//
	void handleCommands();
	void loadNewLevel(int levelNum);

	bool* levelLoaded;
	thread loadLevelThread;
	void levelLoadThreadFunc(int levelNum);
	void detachLevelLoadingThread();
	EnvirementItemManager m_EnviermentItemManager;
	sf::Vector2f itemToCenterOfBlock(sf::Vector2u gridPos);//returns the position to place an item in the center of a block
	bool noThreadLevLoaded;
	Camera* m_Camera;
	int m_currentLevel;
	void startNewGame();
	PlayerInformationSet myInformation;
	bool* m_gameRestarter;
	string m_name;
};
