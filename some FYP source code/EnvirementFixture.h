#pragma once
#include "envirementitem.h"
#include "Player.h"
#include "LevelManager.h"
class EnvirementFixture : public EnvirementItem
{
public:
	EnvirementFixture(void);
	EnvirementFixture(sf::Vector2f position, int id);
	~EnvirementFixture(void);
	bool loadMedia();
	void update(sf::Time timeElasped);
	void react();

private:
	float timeSinceLastImage;
	sf::IntRect m_CurrentImageRect;
};

