#include "stdafx.h"
#include "EnterNameScreen.h"

EnterNameScreen* EnterNameScreen::m_instance;

EnterNameScreen* EnterNameScreen::getInstance()
{
	if(m_instance == 0)
	{
		m_instance = new EnterNameScreen();
	}
	return m_instance;
}

void EnterNameScreen::clearName()
{
	m_nameString = "";
}

EnterNameScreen::EnterNameScreen(void)
{
	m_nameString = "";
	setUpText();
	m_menuBackground = new sf::Sprite();
	ResourceManager::getInstance()->setUpSprite(m_menuBackground, "enterName", GlobalConstantsStore::getInsatnce()->getScreenDimensions());
}

void EnterNameScreen::render()
{
	ResourceManager::getInstance()->getRenderer()->draw(*m_menuBackground);
	m_Text.setString(m_nameString);
	ResourceManager::getInstance()->getRenderer()->draw(m_Text);
}

EnterNameScreen::~EnterNameScreen(void)
{
}

void EnterNameScreen::update()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if(!keyHeld){
			m_nameString.append("a");
		}
		keyHeld = true;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::B))
	{
		if(!keyHeld){
			m_nameString.append("b");
		}
		keyHeld = true;

	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		if(!keyHeld){
			m_nameString.append("c");
		}
		keyHeld = true;

	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if(!keyHeld){
			m_nameString.append("d");
		}
		keyHeld = true;

	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		if(!keyHeld){
			m_nameString.append("e");
		}
		keyHeld = true;

	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{
		if(!keyHeld){
			m_nameString.append("f");
		}
		keyHeld = true;

	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::G))
	{
		if(!keyHeld){
			m_nameString.append("g");
		}
		keyHeld = true;

	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::H))
	{
		if(!keyHeld){
			m_nameString.append("h");
		}
		keyHeld = true;

	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::I))
	{
		if(!keyHeld){
			m_nameString.append("i");
		}
		keyHeld = true;

	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::J))
	{
		if(!keyHeld){
			m_nameString.append("j");
		}
		keyHeld = true;

	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::K))
	{
		if(!keyHeld){
			m_nameString.append("k");
		}
		keyHeld = true;

	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::L))
	{
		if(!keyHeld){
			m_nameString.append("l");
		}
		keyHeld = true;

	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::M))
	{
		if(!keyHeld){
			m_nameString.append("m");
		}
		keyHeld = true;

	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::N))
	{
		if(!keyHeld){
			m_nameString.append("n");
		}
		keyHeld = true;

	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::O))
	{
		if(!keyHeld){
			m_nameString.append("o");
		}
		keyHeld = true;

	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
	{
		if(!keyHeld){
			m_nameString.append("p");
		}
		keyHeld = true;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		if(!keyHeld){
			m_nameString.append("q");
		}
		keyHeld = true;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		if(!keyHeld){
			m_nameString.append("r");
		}
		keyHeld = true;


	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if(!keyHeld){
			m_nameString.append("s");
		}
		keyHeld = true;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::T))
	{
		if(!keyHeld){
			m_nameString.append("t");
		}
		keyHeld = true;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::U))
	{
		if(!keyHeld){
			m_nameString.append("u");
		}
		keyHeld = true;

	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::V))
	{
		if(!keyHeld){
			m_nameString.append("v");
		}
		keyHeld = true;


	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if(!keyHeld){
			m_nameString.append("w");
		}
		keyHeld = true;

	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		if(!keyHeld){
			m_nameString.append("x");
		}
		keyHeld = true;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
	{
		if(!keyHeld){
			m_nameString.append("y");
		}
		keyHeld = true;

	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		if(!keyHeld){
			m_nameString.append("z");
		}
		keyHeld = true;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
	{
		if(m_nameString.size() > 0)
		{
			m_nameString.clear();
		}
	}
	else
	{
		keyHeld = false;
	}
}
	
string EnterNameScreen::acceptSelection()
{
	return m_nameString;
}

void EnterNameScreen::setUpText(){
	messageToDisplay = "";
	m_Font.loadFromFile("Media/Fonts/tahoma.ttf");
	m_Text.setFont(m_Font);
	m_Text.setCharacterSize(30);
	m_Text.setColor(sf::Color::Black);
	m_Text.setString(messageToDisplay);
	m_Text.setPosition(sf::Vector2f(50, 100));
	m_Text.setColor(sf::Color(0,0,0,255));
}