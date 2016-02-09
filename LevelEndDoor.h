#pragma once
#include "envirementitem.h"
#include "Player.h"
#include "LevelManager.h"
#include "ScoreManager.h"
class EnvirementItemManager;

class LevelEndDoor : public EnvirementItem
{
public:
	LevelEndDoor(void);
	LevelEndDoor(sf::Vector2f position, int id, int toLevel, Player* playerPtr, LevelManager* levelManagerPtr, EnumStore::GAME_STATE* gameState);
	~LevelEndDoor(void);
	bool loadMedia();
	void update(sf::Time timeElasped);
	void react(EnvirementItemManager* EIM);

private:
	float timeSinceLastImage;
	sf::IntRect m_CurrentImageRect;
	int m_ToLevel;
	Player* m_Player;
	LevelManager* m_LevelManager;
	EnumStore::GAME_STATE* m_GameState;
};

#include "EnvirementItemManager.h"