#pragma once
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <vector>
#include <list>
#include "EnumStore.h"
#include "AudioManager.h"

using namespace std;
class Messanger
{
public:
	Messanger(const sf::Vector2f* screenSize, float* cameraSizeMultiplier, sf::Vector2f* cameraPosition);
	~Messanger(void);
	sf::Vector2f m_messagePos;
	sf::Vector2f m_messageDimentions;
	sf::Font messageFont;
	string messageToWrite;
	float MessageStayTime;
	sf::Color messageColour;
	sf::Vector2f imageDisplayPos;
	sf::Vector2f imageDisplayDimentions;
	const float imageFadeOutTime;
	float remainingImageFadeOutTime;
	string seperateStringLines(string linelessString, int stringWidth);
	
	list<EnumStore::inventoryItem> itemsInInventory;
	void displayMessage(string messageToDisplay);
	void displayInstantMessage(string messageToDisplay);
	void displayImage(sf::RenderWindow* window);
	const sf::Vector2f* SCREENSIZE;
	
	void Draw(sf::RenderWindow* window);
	void update(sf::Time timeElapsed, EnumStore::GAME_STATE* p_currentGameState);
	void updateClock(std::pair<int, int> p_minsAndSeconds);

private:
	sf::Font m_Font;
	sf::Text m_Text;
	sf::Text m_ScoreText;
	sf::RectangleShape m_messageBack;
	sf::RectangleShape m_scoreBack;
	float messageFadeOutTime;
	int messageAlpha;
	float* m_cameraSizeMultiplier;
	int m_characterSize;
	sf::Vector2f* m_CameraPosition;

};

