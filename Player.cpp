#include "stdafx.h"
#include "Player.h"


Player::Player(LevelManager * levelManager, sf::Vector2f screenSize): 
	m_Position(sf::Vector2f(600,0)), m_Dimentions(sf::Vector2f(30,52)), m_Velocity(sf::Vector2f(0,0)), m_Acceleration(sf::Vector2f(0,0)), 
	WALKSPEED_PS(100.0f), SPRINTSPEED_PS(300.0f), m_levelManager(levelManager), m_FrameTimeLapse(0.0), m_AnimColRow(sf::Vector2i(0,0)),
	m_FrameDimentions(sf::Vector2i(10,10)),
	m_ScreenSize(screenSize), GRAVITY(981.0)
{
	//loadMedia();
	m_Sprite = new sf::Sprite();
	m_imageName = "PlayerSpriteSheet1";
	ResourceManager::getInstance()->setUpSprite(m_Sprite, "PlayerSpriteSheet1", m_Dimentions); 
	m_AnimColRow.y = 0;
	assert(0 == m_AnimColRow.y);
}


Player::~Player(void)
{
}

void Player::update(sf::Time timeElasped){
		keyboardInput(timeElasped);
		genAnimFrame(timeElasped);
		CheckCollision(timeElasped);

		m_Position.x += m_Velocity.x * timeElasped.asSeconds();
		m_Position.y += m_Velocity.y * timeElasped.asSeconds();
		
		m_Sprite->setPosition(m_Position);
}

bool Player::keyboardInput(sf::Time timeElasped){
	m_KeyPressed = false;

	if (Controller::getInstance()->actionLeft())
	{
		m_AnimColRow.y = 1;
		//if(inAir == false){
			if(Controller::getInstance()->actionSprint()){
				m_Velocity.x = -SPRINTSPEED_PS;
			}
			else
			{
				m_Velocity.x = -WALKSPEED_PS;
			}
		//}
		//else{
			//velocity.x = -30.0;
		//}
		m_KeyPressed = true;
	}
	else if (Controller::getInstance()->actionRight())
	{
		m_AnimColRow.y = 2;
		//if(inAir == false){
			if(Controller::getInstance()->actionSprint()){
				m_Velocity.x = SPRINTSPEED_PS;
			}
			else
			{
				m_Velocity.x = WALKSPEED_PS;
			}
		//}
		//else{
			//velocity.x = 30.0;
		//}
		m_KeyPressed = true;
	}
	else if (!inAir){
		m_Velocity.x = 0;
	}

	if (Controller::getInstance()->actionJump())
	{
		jump();
		m_KeyPressed = true;
	}

	return m_KeyPressed;
}

void Player::draw(sf::RenderWindow* window){
	window->draw(*m_Sprite);
}

void Player::CheckCollision(sf::Time timeElasped){
	//horozontal collision
	if(m_Velocity.x != 0){//player moving
		float nextXPos = m_Position.x + m_Velocity.x * timeElasped.asSeconds();
		if(m_Velocity.x > 0){//moving right
			if(nextXPos + m_Dimentions.x > m_levelManager->getWallRight(m_Position, m_Dimentions)){
				m_Velocity.x = 0;
			}
		}
		else if(m_Velocity.x < 0){//moving left
			if(nextXPos < m_levelManager->getWallLeft(m_Position, m_Dimentions)){
				m_Velocity.x = 0;
			}
		}
	}

	//veritcal collision
	double nextYPos = m_Position.y + (m_Velocity.y * timeElasped.asSeconds());
	if(m_levelManager->getFloorLevel(m_Position, m_Dimentions) > nextYPos + m_Dimentions.y){//if in air
		//v= U     +     A    *      T
		m_Velocity.y += (GRAVITY * timeElasped.asSeconds());
		inAir = true;
		nextYPos = m_Position.y + m_Velocity.y * timeElasped.asSeconds();

		if(nextYPos < m_levelManager->getRoofLevel(m_Position, m_Dimentions)){//player top would pass through roof
			if(m_Velocity.y < 0){
				m_Velocity.y = GRAVITY * timeElasped.asSeconds();
				nextYPos = m_Position.y + (m_Velocity.y * timeElasped.asSeconds());
			}
		}
		if((nextYPos + m_Dimentions.y) > m_levelManager->getFloorLevel(m_Position, m_Dimentions)){//would pass through floor
			m_Position.y = m_levelManager->getFloorLevel(m_Position, m_Dimentions) - m_Dimentions.y;
			m_Velocity.y = 0;
			nextYPos = m_Position.y;
			inAir = false;
		}

	}
	else{//not in air
		m_Position.y = m_levelManager->getFloorLevel(m_Position, m_Dimentions) - m_Dimentions.y;
		m_Velocity.y = 0;
		inAir = false;
	}
}

sf::Vector2f Player::getPosition(){
	return m_Position;
}

void Player::setBlockPos(sf::Vector2u gridPos){//puts the player in the center of the block
	m_Position = sf::Vector2f(
		(gridPos.x * m_levelManager->SCREEN_CELL_SIZE.x) + (m_levelManager->SCREEN_CELL_SIZE.x / 2) - (m_Dimentions.x / 2), 
		(gridPos.y * m_levelManager->SCREEN_CELL_SIZE.y));
}

sf::Vector2f Player::getSize(){
	return m_Dimentions;
}

bool Player::jump(){
	if(!inAir){
		m_Velocity.y = -400;
		m_Position.y -= 1;
		AudioManager::getInstance()->playSoundEffect("jump2");
	}
	return true;
}

bool Player::loadMedia(){
	bool retBool = true;
	if(!m_SpriteSheetText.loadFromFile("media/Spritesheets/PlayerSpriteSheet1.png")){
		retBool = false;
	}
	m_FrameDimentions = sf::Vector2i(m_SpriteSheetText.getSize().x / FRAMES_PER_ROW, m_SpriteSheetText.getSize().y / SPRITE_SHEET_ROWS);
	m_SpriteSheetText.setSmooth(false);
	m_Sprite->setTexture(m_SpriteSheetText);
	return retBool;
}

void Player::genAnimFrame(sf::Time timeElasped){
	if(m_KeyPressed && !inAir && m_AnimColRow.y != 0){//animate
		m_FrameTimeLapse += timeElasped.asSeconds();
		if(m_FrameTimeLapse >= 0.1){
			m_AnimColRow.x += 1;
			if(m_AnimColRow.x >= ResourceManager::getInstance()->getAnimationFrames(m_imageName)){
				m_AnimColRow.x = 0;
			}
			m_FrameTimeLapse = 0.0;
		}
	}
	else if (m_AnimColRow.y == 0)
	{
		m_FrameTimeLapse += timeElasped.asSeconds();
		if(m_FrameTimeLapse >= 0.8){
			m_AnimColRow.x += 1;
			if(m_AnimColRow.x * m_FrameDimentions.x >= ResourceManager::getInstance()->getAnimationFrames(m_imageName)){
				m_AnimColRow.x = 0;
			}
			m_FrameTimeLapse = 0.0;
		}

	}
	else if(!m_KeyPressed){
		m_AnimColRow.x = 0;
	}
	
	ResourceManager::getInstance()->updateSpriteFrame(m_Sprite, m_imageName, m_AnimColRow.x, m_AnimColRow.y);
}

float Player::pixleToMeter(float pixle){
	float retFloat = 0;

	//float meter = (pixle * 3) * 

	return retFloat;
}

/*
void Player::checkItems(){
	for(int i = 0; i < m_EnvirementItemsVector->size(); i++){
		if(m_EnvirementItemsVector->at(i)->checkCollision(getPosition(), getSize())){
			m_messanger.displayMessage("action button to pick up");
			if(m_controller->actionAction()){
				setBlockPos(sf::Vector2u(0,9));
			}
		}
	}
}
/*if(m_EnvirementItem.checkCollision(player->getPosition(), player->getSize())){
			m_messanger.displayMessage("action button to pick up");
			if(m_Controller->actionAction()){
				player->setBlockPos(sf::Vector2u(0,9));
			}
		}*/