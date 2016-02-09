#include "stdafx.h"
#include "Inventory.h"


Inventory::Inventory(const sf::Vector2f* screenSize, EnumStore::GAME_STATE* gameStatePoint, Camera* camera): 
	m_Scroll(0), m_NumOfSlots(10), active(false), m_SlotSelected(0), m_GameStatePointer(gameStatePoint), m_Camera(camera)
{
	const float slotSize = 150;
	m_numOfColumns = (screenSize->x / slotSize) - 1;
	m_borderSize = (screenSize->x - (slotSize * m_numOfColumns)) / 2;

	for(int i = 0; i < m_NumOfSlots; i++){
		m_slotVector.push_back(new InventorySlot(i,m_borderSize,m_numOfColumns, new float(m_Scroll), slotSize));
	}
	m_slotVector.at(m_SlotSelected)->setSelected(true);
	loadMedia(screenSize);
}


Inventory::~Inventory(void)
{
}

void Inventory::draw(sf::RenderWindow* window){
	if(active){
		window->draw(m_backSprite);

		for(int i = 0; i < m_slotVector.size(); i++){
			m_slotVector.at(i)->draw(window);
		}
	}
}

bool Inventory::loadMedia(const sf::Vector2f* screenSize){
	bool retBool = true;
	if(!m_backText.loadFromFile("media/Images/inventoryBackground.png")){
		retBool = false;
	}
	m_backText.setSmooth(false);
	m_backSprite.setTexture(m_backText);

	float xScale = screenSize->x / m_backText.getSize().x;
	float yScale = screenSize->y / m_backText.getSize().y;
	m_backSprite.setScale(xScale, yScale);
	m_backSprite.setPosition(0.0f,0.0f);
	return retBool;
}

bool Inventory::toggle(){
	if(*m_GameStatePointer == EnumStore::GAME_STATE::IN_GAME){
		active = !active;
		m_Camera->jumpToZoom(0, sf::Vector2f(0,0));
		*m_GameStatePointer = EnumStore::GAME_STATE::IN_INVENTORY;
	}
	else if(*m_GameStatePointer == EnumStore::GAME_STATE::IN_INVENTORY){
		active = !active;
		m_Camera->toggleSnapZoom();
		*m_GameStatePointer = EnumStore::GAME_STATE::IN_GAME;
	}


	return active;
}

void Inventory::clearInventory()
{
	for(int i = 0; i < m_NumOfSlots; i++){
		m_slotVector.at(i)->clearSlot();
	}
}

bool Inventory::isActive(){
	return active;
}

void Inventory::update(){
	if(isActive()){
		if(Controller::getInstance()->actionRightOnce()){
			m_slotVector.at(m_SlotSelected)->setSelected(false);
			if(m_SlotSelected == m_NumOfSlots -1){
				m_SlotSelected = 0;
			}
			else m_SlotSelected++;
		}
		else if(Controller::getInstance()->actionLeftOnce()){
			m_slotVector.at(m_SlotSelected)->setSelected(false);
			if(m_SlotSelected == 0){
				m_SlotSelected = m_NumOfSlots - 1;
			}
			else m_SlotSelected--;
		}
		m_slotVector.at(m_SlotSelected)->setSelected(true);

		if(Controller::getInstance()->actionMenuReturn() || Controller::getInstance()->actionInventory()){
			toggle();
		}
	}
	if(Controller::getInstance()->actionInventory()){
		toggle();
	}
}

void Inventory::addToInventory(EnumStore::inventoryItem itemToAdd, int quantity){
	bool itemAdded = false;

	for(int i = 0; i < m_NumOfSlots && !itemAdded; i++){
		if(m_slotVector.at(i)->getItem() == itemToAdd){
			for(;quantity > 0; quantity--){
				m_slotVector.at(i)->addItem();
			}
			itemAdded = true;
		}
	}
	if(!itemAdded){
		for(int i = 0; i < m_NumOfSlots && !itemAdded; i++){
			if(m_slotVector.at(i)->getItem() == EnumStore::inventoryItem::empty){
				m_slotVector.at(i)->assignToSlot(itemToAdd);
				quantity--;
				for(;quantity > 0; quantity--){
					m_slotVector.at(i)->addItem();
				}
				itemAdded = true;
			}
		}
	}
}