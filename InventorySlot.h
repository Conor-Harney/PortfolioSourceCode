#pragma once
#include <string>
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include "EnumStore.h"
using namespace std;
class InventorySlot
{
public:
	InventorySlot(int slotNumber, float inventoryBorderSize, int numOfColumns, float* scroll, float slotSize);
	~InventorySlot(void);
	void draw(sf::RenderWindow* window);
	void assignToSlot(EnumStore::inventoryItem item);
	void addItem();//add 1 more of the already assigned item
	EnumStore::inventoryItem getItem();//return the item contained
	int getId();
	int getQuantity();//return the quantity of contained items
	void setSelected(bool);
	void clearSlot();

private:
	int m_SlotNumber;
	EnumStore::inventoryItem m_item;
	int m_NumberOfItemsInSlot;
	sf::Vector2f m_PositionInInventory;//the position relitive to the top of the inventory, not including the amount the player has scrolled down.
	float *m_scroll;//the amount the player has scrolled down the inventory
	sf::Vector2f m_position;//position relitive to the screen (m_PositionInInventory - m_scroll)
	const sf::Vector2f DIMENTIONS;

	sf::Texture spriteSheetText;
	sf::Sprite m_GridSprite;
	bool loadMedia();
	bool m_Selected; //is this slot currently selected

	sf::IntRect textureRect2;

	sf::Texture ItemSpriteSheetText;
	sf::Sprite m_ItemSprite;
	bool loadItemImage();
	

	void setUpText();
	sf::Font m_Font;
	sf::Text m_Text;
	string messageToDisplay;
};


