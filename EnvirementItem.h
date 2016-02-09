#pragma once
//this is a base class for all envirement items to be stored in the level manager
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include "EnumStore.h"

class EnvirementItem
{
public:
	
	EnvirementItem(sf::Vector2f position, int id);
	~EnvirementItem(void);
	int getID();
	sf::Vector2f getPosition();
	sf::Vector2f getDimensions();
	std::string itemName;
	virtual void update();
	virtual void render(sf::RenderWindow* window);
	bool checkCollision(sf::Vector2f position, sf::Vector2f dimentions);
	EnumStore::EnvirementItemType getType();
	virtual void react();//react to player interaction
	

protected:
	EnumStore::EnvirementItemType m_EnvirementItemType;
	EnvirementItem();
	sf::Vector2f m_position;
	sf::Vector2f m_dimensions;
	sf::Vector2u m_SpriteSheetDimentions;
	sf::Vector2u m_SpriteSheetImageSize;//the size of a single image on the sprite sheet
	int m_itemID;
	sf::Texture m_SpriteSheetText;
	sf::Sprite m_Sprite;
	virtual bool loadMedia();
};

