#pragma once
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
class GlobalConstantsStore
{
public:
	GlobalConstantsStore(void);
	~GlobalConstantsStore(void);
	static GlobalConstantsStore* getInsatnce();
	void init(sf::Vector2f p_screenDimensions);
	sf::Vector2f getScreenDimensions();

private:
	static GlobalConstantsStore* m_instance;
	sf::Vector2f SCREEN_DIMENSIONS;
};

