#include "stdafx.h"
#include "EnvirementItemManager.h"


EnvirementItemManager::EnvirementItemManager(){

}

EnvirementItemManager::EnvirementItemManager(Player* playerPtr, Messanger* messangerPtr, LevelManager* levelManagerPtr, EnumStore::GAME_STATE* gameStatePtr, Inventory* inventory): 
	m_EnvirementItemsVector(new vector<EnvirementItem*>()), m_Player(playerPtr), 
	m_Messanger(messangerPtr), m_LevelManager(levelManagerPtr), m_GmaeState(gameStatePtr), m_Inventory(inventory)
{
	m_PickupSizesMap[EnumStore::inventoryItem::battery] = sf::Vector2f(30,30);
	m_PickupSizesMap[EnumStore::inventoryItem::potion] = sf::Vector2f(30,30);
	loadLevelItems(0,0);
}

void EnvirementItemManager::loadLevelItems(int levelNum, int sceneNum){
	m_EnvirementItemsVector->clear();
	if(m_LevelManager->getLevelSet() == 0){
		m_EnvirementItemsVector->push_back(new LevelEndDoor(itemToCenterOfBlock(sf::Vector2u(0,1),sf::Vector2f(m_LevelManager->SCREEN_CELL_SIZE.x / 2,m_LevelManager->SCREEN_CELL_SIZE.y), false),0, 1, m_Player, m_LevelManager, m_GmaeState));
		m_EnvirementItemsVector->push_back(new Pickup(itemToCenterOfBlock(sf::Vector2u(1,9),m_PickupSizesMap[EnumStore::inventoryItem::battery], true), 2, EnumStore::inventoryItem::battery, m_Inventory));
		m_EnvirementItemsVector->push_back(new Pickup(itemToCenterOfBlock(sf::Vector2u(2,9),sf::Vector2f(30,30), true), 3, EnumStore::inventoryItem::potion, m_Inventory));
		
	}
	else if(m_LevelManager->getLevelSet() == 1){
		m_EnvirementItemsVector->push_back(new LevelEndDoor(itemToCenterOfBlock(sf::Vector2u(0,0),sf::Vector2f(m_LevelManager->SCREEN_CELL_SIZE.x / 2,m_LevelManager->SCREEN_CELL_SIZE.y), false),0, 2, m_Player, m_LevelManager, m_GmaeState));
		m_EnvirementItemsVector->push_back(new Pickup(itemToCenterOfBlock(sf::Vector2u(9,1),m_PickupSizesMap[EnumStore::inventoryItem::potion], true), 1, EnumStore::inventoryItem::potion, m_Inventory));
	}
	else if(m_LevelManager->getLevelSet() == 2){
		m_EnvirementItemsVector->push_back(new LevelEndDoor(itemToCenterOfBlock(sf::Vector2u(0,1),sf::Vector2f(m_LevelManager->SCREEN_CELL_SIZE.x / 2,m_LevelManager->SCREEN_CELL_SIZE.y), false),0, 3, m_Player, m_LevelManager, m_GmaeState));
		m_EnvirementItemsVector->push_back(new Pickup(itemToCenterOfBlock(sf::Vector2u(9,0),m_PickupSizesMap[EnumStore::inventoryItem::potion], true), 1, EnumStore::inventoryItem::potion, m_Inventory));
	}
	else if(m_LevelManager->getLevelSet() == 3){
		m_EnvirementItemsVector->push_back(new LevelEndDoor(itemToCenterOfBlock(sf::Vector2u(9,3),sf::Vector2f(m_LevelManager->SCREEN_CELL_SIZE.x / 2,m_LevelManager->SCREEN_CELL_SIZE.y), false),0, -1, m_Player, m_LevelManager, m_GmaeState));
		m_EnvirementItemsVector->push_back(new Pickup(itemToCenterOfBlock(sf::Vector2u(1,1),sf::Vector2f(30,30), true), 1, EnumStore::inventoryItem::potion, m_Inventory));
	}
}

EnvirementItemManager::~EnvirementItemManager(void)
{
}

void EnvirementItemManager::update(sf::Time timeElapsed){
	for(int i = 0; i < m_EnvirementItemsVector->size(); i++){
		if(m_EnvirementItemsVector->at(i)->getType() == EnumStore::EnvirementItemType::EnvirementFixture){
			(dynamic_cast<EnvirementFixture*> (m_EnvirementItemsVector->at(i)))->update(timeElapsed);
		}
		else if(m_EnvirementItemsVector->at(i)->getType() == EnumStore::EnvirementItemType::Pickup){
			(dynamic_cast<Pickup*> (m_EnvirementItemsVector->at(i)))->update(timeElapsed);
		}
		else if(m_EnvirementItemsVector->at(i)->getType() == EnumStore::EnvirementItemType::LevelEndDoor){
			(dynamic_cast<LevelEndDoor*> (m_EnvirementItemsVector->at(i)))->update(timeElapsed);
		}
	}
	checkForInteraction();
}

void EnvirementItemManager::render(sf::RenderWindow* window){
	for(int i = 0; i < m_EnvirementItemsVector->size(); i++){
		if(m_EnvirementItemsVector->at(i)->getType() == EnumStore::EnvirementItemType::EnvirementFixture){
			(dynamic_cast<EnvirementFixture*> (m_EnvirementItemsVector->at(i)))->render(window);
		}
		else if(m_EnvirementItemsVector->at(i)->getType() == EnumStore::EnvirementItemType::Pickup){
			(dynamic_cast<Pickup*> (m_EnvirementItemsVector->at(i)))->render(window);
		}
		else if(m_EnvirementItemsVector->at(i)->getType() == EnumStore::EnvirementItemType::LevelEndDoor){
			(dynamic_cast<LevelEndDoor*> (m_EnvirementItemsVector->at(i)))->render(window);
		}
	}
}

void EnvirementItemManager::checkForInteraction(){
	for(int i = 0; i < m_EnvirementItemsVector->size(); i++){
		sf::Vector2f testPos = m_Player->getPosition();
		sf::Vector2f testSize = m_Player->getSize();
		if(m_EnvirementItemsVector->at(i)->checkCollision(m_Player->getPosition(), m_Player->getSize())){

			if(m_EnvirementItemsVector->at(i)->getType() == EnumStore::EnvirementItemType::EnvirementFixture){
				m_Messanger->displayInstantMessage("action button to interact");
				if(Controller::getInstance()->actionAction()){
					(dynamic_cast<EnvirementFixture*> (m_EnvirementItemsVector->at(i)))->react();
				}
			}

			else if(m_EnvirementItemsVector->at(i)->getType() == EnumStore::EnvirementItemType::Pickup){
				m_Messanger->displayInstantMessage("action button to pick up");
				if(Controller::getInstance()->actionAction()){
					//(dynamic_cast<Pickup*> (m_EnvirementItemsVector->at(i)))->react(i);
					CollectPickup(i);
				}
			}

			else if(m_EnvirementItemsVector->at(i)->getType() == EnumStore::EnvirementItemType::LevelEndDoor){
				m_Messanger->displayInstantMessage("action button leave");
				if(Controller::getInstance()->actionAction()){
					(dynamic_cast<LevelEndDoor*> (m_EnvirementItemsVector->at(i)))->react(this);
				}
			}

		}
	}
}

sf::Vector2f EnvirementItemManager::itemToCenterOfBlock(sf::Vector2u gridPos, sf::Vector2f itemDimensions, bool centerY){
	float xPos = (gridPos.x * m_LevelManager->SCREEN_CELL_SIZE.x) + (m_LevelManager->SCREEN_CELL_SIZE.x / 2) - (itemDimensions.x / 2);
	float yPos = (gridPos.y * m_LevelManager->SCREEN_CELL_SIZE.y);
	if(centerY){yPos += ((m_LevelManager->SCREEN_CELL_SIZE.y / 2) -(itemDimensions.y / 2));}
	sf::Vector2f retPos = sf::Vector2f(xPos, yPos);
	return retPos;
}

void EnvirementItemManager::CollectPickup(int referenceNumber){
	(dynamic_cast<Pickup*> (m_EnvirementItemsVector->at(referenceNumber)))->react(referenceNumber);
	ScoreManager::getInstance()->addToScore((dynamic_cast<Pickup*> (m_EnvirementItemsVector->at(referenceNumber)))->getValue());
	m_Inventory->addToInventory((dynamic_cast<Pickup*> (m_EnvirementItemsVector->at(referenceNumber)))->getType(), 1);
	m_EnvirementItemsVector->erase(m_EnvirementItemsVector->begin() + referenceNumber);
}