#include "stdafx.h"
#include "EnvirementFixture.h"


EnvirementFixture::EnvirementFixture(void)
{
	m_dimensions = sf::Vector2f(50,90);
	m_position = sf::Vector2f(0,0);
	m_itemID = 0;
	loadMedia();
	timeSinceLastImage = 0;
	m_EnvirementItemType = EnumStore::EnvirementItemType::EnvirementFixture;
}

EnvirementFixture::EnvirementFixture(sf::Vector2f position, int id)
{	
	m_dimensions = sf::Vector2f(50,90);
	m_position = sf::Vector2f(position.x - (m_dimensions.x / 2), position.y - (m_dimensions.y / 2));
	m_itemID = id;
	loadMedia();
	timeSinceLastImage = 0;
	m_EnvirementItemType = EnumStore::EnvirementItemType::EnvirementFixture;
}


EnvirementFixture::~EnvirementFixture(void)
{
}

void EnvirementFixture::update(sf::Time timeElasped){
	//m_Sprite.setPosition(m_position);
	timeSinceLastImage += timeElasped.asSeconds();
	if(timeSinceLastImage > 0.2){
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

bool EnvirementFixture::loadMedia(){
	bool retBool = true;
	if(!m_SpriteSheetText.loadFromFile("media/Spritesheets/portalSS1.png")){
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

void EnvirementFixture::react(){
	//playerPtr->setBlockPos(sf::Vector2u(0,9));
	//levelManagerPtr->
}