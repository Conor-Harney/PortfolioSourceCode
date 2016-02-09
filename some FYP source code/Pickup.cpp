#include "stdafx.h"
#include "Pickup.h"

//to add a new pickup:
//add sprite sheet - 5 (10x10) images - horozontal
//include name in enumstore : inventoryItem
//add loadMedia() case statement
//add inventory image
//add inventoryslot - loadItemImage() case statement


Pickup::Pickup(sf::Vector2f position, int id, EnumStore::inventoryItem itemType, Inventory* inventory)
{	
	m_dimensions = sf::Vector2f(30,30);
	m_position = position;
	m_itemID = id;
	timeSinceLastImage = 0;
	m_EnvirementItemType = EnumStore::EnvirementItemType::Pickup;
	m_ItemType = itemType;
	if(m_ItemType == EnumStore::inventoryItem::potion){m_scoreValue = 30;}
	else if(m_ItemType == EnumStore::inventoryItem::battery){m_scoreValue = 20;}
	m_inventory = inventory;
	loadMedia();
}

Pickup::Pickup(){//this should never be invoked
	bool breaaker = true;
}

Pickup::~Pickup(void)
{
}

void Pickup::update(sf::Time timeElasped){
	//m_Sprite.setPosition(m_position);
	timeSinceLastImage += timeElasped.asSeconds();
	if(timeSinceLastImage > 1){
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

void Pickup::react(int referenceNumber){
//	m_inventory->addToInventory(m_ItemType, 1);
//	EIM->DestroyPickup(referenceNumber);
}

bool Pickup::loadMedia(){
	bool retBool = true;
	string directory = "";

	switch(m_ItemType){
	case EnumStore::inventoryItem::potion:
		directory = "media/Spritesheets/BottlePickupSS.png";
		break;
	case EnumStore::inventoryItem::battery:
		directory = "media/Spritesheets/BatteryPickupSS.png";
		break;
	default:
		directory = "media/Spritesheets/BottlePickupSS.png";
		break;
	}

	if(!m_SpriteSheetText.loadFromFile(directory)){
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

int Pickup::getValue()
{
	return m_scoreValue;
}

EnumStore::inventoryItem Pickup::getType()
{
	return m_ItemType;
}