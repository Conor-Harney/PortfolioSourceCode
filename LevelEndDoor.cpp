#include "stdafx.h"
#include "LevelEndDoor.h"

LevelEndDoor::LevelEndDoor(void)
{
	m_dimensions = sf::Vector2f(50,90);
	m_position = sf::Vector2f(0,0);
	m_itemID = 0;
	loadMedia();
	timeSinceLastImage = 0;
	m_EnvirementItemType = EnumStore::EnvirementItemType::LevelEndDoor;
}

LevelEndDoor::LevelEndDoor
	(sf::Vector2f position, int id, int toLevel, Player* playerPtr, LevelManager* levelManagerPtr, EnumStore::GAME_STATE* gameState)
{
	m_ToLevel = toLevel;
	m_dimensions = sf::Vector2f(levelManagerPtr->SCREEN_CELL_SIZE.x / 2,levelManagerPtr->SCREEN_CELL_SIZE.y);
	m_position = position;
	m_itemID = id;
	loadMedia();
	timeSinceLastImage = 0;
	m_EnvirementItemType = EnumStore::EnvirementItemType::LevelEndDoor;
	m_LevelManager = levelManagerPtr;
	m_Player = playerPtr;
	m_GameState = gameState;
}


LevelEndDoor::~LevelEndDoor(void)
{
}

void LevelEndDoor::update(sf::Time timeElasped){
	//m_Sprite.setPosition(m_position);
	timeSinceLastImage += timeElasped.asSeconds();
	if(timeSinceLastImage > 0.2){
		timeSinceLastImage = 0;
		if (m_CurrentImageRect.left + m_CurrentImageRect.width != m_SpriteSheetDimentions.x)
		{//there ia another frame in the spritesheet
			m_CurrentImageRect.left += m_SpriteSheetImageSize.x;
		}
		else{//restart from the start of the spritesheet
			m_CurrentImageRect.left = 0;
		}
		m_Sprite.setTextureRect(m_CurrentImageRect);
	}
}

bool LevelEndDoor::loadMedia(){
	bool retBool = true;
	if(!m_SpriteSheetText.loadFromFile("media/Spritesheets/portalSS1.png")){
		retBool = false;
	}
	m_SpriteSheetImageSize = sf::Vector2u(10,10);
	m_SpriteSheetDimentions = m_SpriteSheetText.getSize();
	m_SpriteSheetText.setSmooth(false);
	m_Sprite.setTexture(m_SpriteSheetText);
	m_CurrentImageRect = sf::IntRect(0,0,m_SpriteSheetImageSize.x,m_SpriteSheetImageSize.y);
	m_Sprite.setTextureRect(m_CurrentImageRect);
	m_Sprite.setPosition(m_position);
	m_Sprite.setScale(m_dimensions.x / m_SpriteSheetImageSize.x, m_dimensions.y / m_SpriteSheetImageSize.y); 
	return retBool;
}

void LevelEndDoor::react(EnvirementItemManager* EIM){
	if(m_ToLevel != -1){
		ScoreManager::getInstance()->nextLevel(m_ToLevel - 1);
		m_Player->setBlockPos(sf::Vector2u(0,9));
		m_LevelManager->setLevelSet(m_ToLevel);
		*m_GameState = EnumStore::GAME_STATE::LOADING;
		m_LevelManager->buildTiledLevel(0);
		EIM->loadLevelItems(m_ToLevel,0);
	}
	else
	{//tolevel = -1
		ScoreManager::getInstance()->nextLevel(3);
		m_Player->setBlockPos(sf::Vector2u(0,9));
		m_LevelManager->setLevelSet(m_ToLevel);
		*m_GameState = EnumStore::GAME_STATE::LOADING;
		m_LevelManager->buildTiledLevel(0);
		EIM->loadLevelItems(m_ToLevel,0);
		*m_GameState = EnumStore::GAME_STATE::SCOREBOARD;
	}

}