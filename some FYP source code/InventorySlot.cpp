#include "stdafx.h"
#include "InventorySlot.h"


InventorySlot::InventorySlot(int slotNumber, float inventoryBorderSize, int numOfColumns, float* scroll, float slotSize): 
	m_SlotNumber(slotNumber), m_NumberOfItemsInSlot(0),m_item(EnumStore::inventoryItem::empty),m_scroll(scroll), DIMENTIONS(slotSize,slotSize), m_Selected(false)
{

	float yPos = 0;
	while(slotNumber >= numOfColumns){
		yPos++;
		slotNumber -= numOfColumns;
	}

	float xPos = inventoryBorderSize + (DIMENTIONS.x * slotNumber);
	yPos = (yPos * DIMENTIONS.y) + inventoryBorderSize;

	m_PositionInInventory = sf::Vector2f(xPos, yPos);
	m_position = m_PositionInInventory + sf::Vector2f(0,*m_scroll);

	loadMedia();
	m_GridSprite.setScale(DIMENTIONS.x / (spriteSheetText.getSize().x / 2),DIMENTIONS.y / spriteSheetText.getSize().y);
	m_GridSprite.setPosition(m_position);
	setUpText();

}

void InventorySlot::clearSlot()
{
	m_NumberOfItemsInSlot = 0;
	messageToDisplay = "";
	m_Text.setString(messageToDisplay);
	m_item = (EnumStore::inventoryItem::empty);
}

InventorySlot::~InventorySlot(void)
{
}

void InventorySlot::draw(sf::RenderWindow* window){
	
	if(m_item != EnumStore::inventoryItem::empty){
		window->draw(m_ItemSprite);
	}
	window->draw(m_GridSprite);
	window->draw(m_Text);
	
}

bool InventorySlot::loadMedia(){
	bool retBool = true;
	if(!spriteSheetText.loadFromFile("media/spritesheets/inventoryTileBases.png")){
		retBool = false;
	}
	spriteSheetText.setSmooth(false);
	m_GridSprite.setTexture(spriteSheetText);
	const sf::IntRect textureRect = sf::IntRect(0,0,spriteSheetText.getSize().x / 2, spriteSheetText.getSize().y);
	m_GridSprite.setTextureRect(textureRect);
	return retBool;
}

void InventorySlot::setSelected(bool selected){
	m_Selected = selected;
	if(m_Selected){
		const sf::IntRect textureRect = sf::IntRect(spriteSheetText.getSize().x / 2,0,spriteSheetText.getSize().x / 2, spriteSheetText.getSize().y);
		m_GridSprite.setTextureRect(textureRect);
	}
	else{
		const sf::IntRect textureRect = sf::IntRect(0,0,spriteSheetText.getSize().x / 2, spriteSheetText.getSize().y);
		m_GridSprite.setTextureRect(textureRect);
	}
}

void InventorySlot::addItem(){
	m_NumberOfItemsInSlot++;
	messageToDisplay = " X" + std::to_string(m_NumberOfItemsInSlot);
	m_Text.setString(messageToDisplay);
}

EnumStore::inventoryItem InventorySlot::getItem(){
	return m_item;
}

int InventorySlot::getId(){
	return m_SlotNumber;
}
	
int InventorySlot::getQuantity(){
	return m_NumberOfItemsInSlot;
}

void InventorySlot::assignToSlot(EnumStore::inventoryItem item){
	m_item = item;
	loadItemImage();
	addItem();
}

bool InventorySlot::loadItemImage(){
	bool retBool = true;

	if(m_item != EnumStore::inventoryItem::empty){
		string directory = "";
		switch(m_item){
		case EnumStore::inventoryItem::potion:
			directory = "media/Images/Potion.png";
			break;
		case EnumStore::inventoryItem::battery:
			directory = "media/Images/Battery.png";
			break; 
		default:
			break;
		}
		if(!ItemSpriteSheetText.loadFromFile(directory)){
			retBool = false;
		}

		m_ItemSprite.setTexture(ItemSpriteSheetText);
		textureRect2 = sf::IntRect(0,0,ItemSpriteSheetText.getSize().x, ItemSpriteSheetText.getSize().y);
		m_ItemSprite.setTextureRect(textureRect2);
		m_ItemSprite.setPosition(m_position);
		m_ItemSprite.setScale(DIMENTIONS.x / ItemSpriteSheetText.getSize().x, DIMENTIONS.y / ItemSpriteSheetText.getSize().y);
	}
	return retBool;
}

void InventorySlot::setUpText(){
	messageToDisplay = "";
	m_Font.loadFromFile("Media/Fonts/tahoma.ttf");
	m_Text.setFont(m_Font);
	m_Text.setCharacterSize(30);
	m_Text.setColor(sf::Color::White);
	m_Text.setString(messageToDisplay);
	m_Text.setPosition(m_position);
	m_Text.setColor(sf::Color(0,0,0,255));
}