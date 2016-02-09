#pragma once
#include <string>
#include <list>
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include "ResourceManager.h"
#include "GlobalConstantsStore.h"
using namespace std;
class EnterNameScreen
{
public:
	static EnterNameScreen* getInstance();
	EnterNameScreen(void);
	~EnterNameScreen(void);
	void update();
	string acceptSelection();
	void render();
	void clearName();

private:
	static EnterNameScreen* m_instance;
	string m_nameString;
	list<char> m_nameCharList;
	bool keyHeld;
	void setUpText();
	sf::Font m_Font;
	sf::Text m_Text;
	string messageToDisplay;
	sf::Sprite* m_menuBackground;



};

