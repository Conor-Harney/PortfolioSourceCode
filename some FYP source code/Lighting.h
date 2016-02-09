#pragma once
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 

class Lighting
{
public:
	Lighting(void);
	~Lighting(void);
	void render(sf::RenderWindow* window);
	void update(sf::Vector2f playerPosition, sf::Vector2f playerSize);
	bool loadMedia();
	void toggle();
private:
	sf::Texture m_Texture;
	sf::Sprite m_Sprite;
	sf::Vector2f m_position;
	bool m_lightingOn;
};

