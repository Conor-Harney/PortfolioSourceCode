#pragma once
#include <vector>
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <string>
#include "LevelManager.h"
#include "AnimationFSM.h"
#include "Controller.h"
#include "AudioManager.h"
#include <assert.h>
#include <stdio.h>
#include "ResourceManager.h"

using namespace std;

class Player
{
public:
	Player(LevelManager* levelManager, sf::Vector2f screenSize);
	~Player(void);
	void update(sf::Time timeElasped);

	void draw(sf::RenderWindow* window);
	
	sf::Vector2f getPosition();
	void setBlockPos(sf::Vector2u gridPos);
	sf::Vector2f getSize();
	

private:
	bool loadMedia();
	bool keyboardInput(sf::Time timeElasped);
	sf::Vector2f m_Position;
	sf::Vector2f m_Dimentions;
	sf::Vector2f m_Velocity;
	sf::Vector2f m_Acceleration;
	string m_Direction;
	const float WALKSPEED_PS;//walk speed per second
	const float SPRINTSPEED_PS;//walk speed per second
	void CheckCollision(sf::Time timeElasped);
	LevelManager* m_levelManager;
	bool jump();
	AnimationFSM stateMachine;
	bool inAir;

	void genAnimFrame(sf::Time timeElasped);//set the section of the sprite sheet being displayed
	
	sf::Texture m_SpriteSheetText;
	sf::Sprite* m_Sprite;
	sf::Vector2i m_AnimColRow;
	static const int SPRITE_SHEET_ROWS = 3;
	static const int FRAMES_PER_ROW = 4;
	sf::Vector2i m_FrameDimentions;
	float m_FrameTimeLapse;
	bool m_KeyPressed;
	sf::Vector2f m_ScreenSize;
	const float GRAVITY;
	void checkItems();
	string m_imageName;

	float pixleToMeter(float pixle);

};

