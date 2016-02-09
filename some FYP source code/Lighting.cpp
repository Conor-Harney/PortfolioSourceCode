#include "stdafx.h"
#include "Lighting.h"


Lighting::Lighting(void)
{
	m_lightingOn = false;
}


Lighting::~Lighting(void)
{
}

void Lighting::render(sf::RenderWindow* window){
	if(m_lightingOn){
		window->draw(m_Sprite);
	}
}

void Lighting::update(sf::Vector2f playerPosition, sf::Vector2f playerSize){
	m_position.x = playerPosition.x - (m_Texture.getSize().x / 2) + (playerSize.x / 2);
	m_position.y = playerPosition.y - (m_Texture.getSize().y / 2) + (playerSize.y / 2);
	m_Sprite.setPosition(m_position);
}

bool Lighting::loadMedia(){
	bool retBool = true;
	if(!m_Texture.loadFromFile("media/Images/LightingImage.png")){
		retBool = false;
	}
	m_Texture.setSmooth(true);
	m_Sprite.setTexture(m_Texture);
	m_Sprite.setColor(sf::Color(0,0,0,245));
	
	return retBool;
}

void Lighting::toggle(){
	m_lightingOn = !m_lightingOn;
}