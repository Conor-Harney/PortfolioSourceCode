#pragma once
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <list>
#include <vector>
#include "Controller.h"
#include "InventorySlot.h"
#include "EnumStore.h"
#include "Camera.h"
using namespace std;

class Inventory
{
public:
	Inventory(const sf::Vector2f* screenSize, EnumStore::GAME_STATE* gameStatePoint, Camera* camera);
	~Inventory(void);
	void draw(sf::RenderWindow* window);

	bool toggle();
	bool isActive();
	int getSlotSelected();
	void setSlotSelected(int slotNum);
	void update();
	void addToInventory(EnumStore::inventoryItem itemToAdd, int quantity);
	void clearInventory();

private:
	float m_Scroll;
	int m_NumOfSlots;
	float m_borderSize;
	vector<InventorySlot*> m_slotVector;

	int m_numOfColumns;
	bool active;
	sf::Texture m_backText;
	sf::Sprite m_backSprite;
	bool loadMedia(const sf::Vector2f* screenSize);
	int m_SlotSelected;
	EnumStore::GAME_STATE* m_GameStatePointer;
	Camera* m_Camera;
};