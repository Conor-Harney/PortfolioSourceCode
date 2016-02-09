#pragma once
#include "EnvirementItem.h"
#include "EnvirementFixture.h"
#include "Pickup.h"
#include <vector>
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp"
#include "Player.h"
#include "Controller.h"
#include "Messanger.h"
#include "LevelEndDoor.h"
#include "LevelManager.h"
#include "Inventory.h"
#include <map>
#include "ScoreManager.h"

using namespace std;

class EnvirementItemManager
{
public:
	EnvirementItemManager();
	EnvirementItemManager(Player* playerPtr, Messanger* messangerPtr, LevelManager* levelManagerPtr, EnumStore::GAME_STATE* gameStatePtr, Inventory* inventory);
	~EnvirementItemManager(void);
	void update(sf::Time timeElapsed);
	void render(sf::RenderWindow* window);
	void loadLevelItems(int levelNum, int sceneNum);
	void CollectPickup(int referenceNumber);

private:
	vector<EnvirementItem*>* m_EnvirementItemsVector;
	Player* m_Player;
	void checkForInteraction();
	Messanger* m_Messanger;
	LevelManager* m_LevelManager;
	EnumStore::GAME_STATE* m_GmaeState;
	sf::Vector2f itemToCenterOfBlock(sf::Vector2u gridPos, sf::Vector2f itemDimensions, bool centerY);
	Inventory* m_Inventory;
	map<EnumStore::inventoryItem, sf::Vector2f> m_PickupSizesMap; 

};

