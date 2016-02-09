#include "stdafx.h"
#include "EnvirementItem.h"

EnvirementItem::EnvirementItem(){
	//must be overwritten to include the ID
}

EnvirementItem::EnvirementItem(sf::Vector2f position, int id): 
	m_position(position), m_dimensions(sf::Vector2f(10,10)), m_itemID(id)
{
}

EnvirementItem::~EnvirementItem(void)
{
}

int EnvirementItem::getID(){
	return m_itemID;
}

sf::Vector2f EnvirementItem::getPosition(){
	return m_position;
}

sf::Vector2f EnvirementItem::getDimensions(){
	return m_dimensions;
}

void EnvirementItem::update(){
	m_Sprite.setPosition(m_position);
}

void EnvirementItem::render(sf::RenderWindow* window){
	window->draw(m_Sprite);
}

bool EnvirementItem::checkCollision(sf::Vector2f position, sf::Vector2f dimentions){
	bool retBool = false;

	if(m_position.x + m_dimensions.x > position.x && m_position.x < position.x + dimentions.x){
		if(m_position.y + m_dimensions.y > position.y && m_position.y < position.y + dimentions.y){
			retBool = true;
		}
	}

	return retBool;
}

bool EnvirementItem::loadMedia(){
	bool retBool = true;

	return true;
}

EnumStore::EnvirementItemType EnvirementItem::getType(){
	return m_EnvirementItemType;
}

void EnvirementItem::react(){

}
