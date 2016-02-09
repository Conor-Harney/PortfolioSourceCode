#pragma once
#include "Envirementitem.h"
#include "Inventory.h"
class EnvirementItemManager;
class Pickup : public EnvirementItem
{
public:
	Pickup(sf::Vector2f position, int id, EnumStore::inventoryItem itemType, Inventory* inventory);
	Pickup();
	~Pickup(void);
	bool loadMedia();
	void update(sf::Time timeElasped);
	void react(int referenceNumber);
	int getValue();
	EnumStore::inventoryItem getType();

private:
	float timeSinceLastImage;
	sf::IntRect m_CurrentImageRect;
	EnumStore::inventoryItem m_ItemType;
	Inventory* m_inventory;
	int m_scoreValue;

};

#include "EnvirementItemManager.h"