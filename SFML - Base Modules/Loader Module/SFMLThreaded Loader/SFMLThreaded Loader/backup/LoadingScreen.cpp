#include "LoadingScreen.h"

LoadingScreen* LoadingScreen::m_instance;
std::mutex lSMu;

LoadingScreen::LoadingScreen()
{

}

LoadingScreen* LoadingScreen::getInstance()
{
	std::lock_guard<std::mutex> guard(lSMu);
	if(m_instance == 0)
	{
		m_instance = new LoadingScreen();
	}
	return m_instance;
}

void LoadingScreen::run(sf::RenderWindow* windowRef)
{
	windowRef->setActive(true);
	//load a font
	sf::Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\GARA.TTF");
	//create a formatted text string
    sf::Text text;
    text.setFont(font);
	text.setStyle(sf::Text::Underlined| sf::Text::Italic | sf::Text::Bold);
    text.setPosition(20,40);
    text.setCharacterSize(40);
	string textString;
	while(Loader::getInstance()->getPercentLoaded() < 100)
	{
		textString = "loading: " + std::to_string(Loader::getInstance()->getPercentLoaded()) + "...";
		text.setString(textString);
		windowRef->clear();
		windowRef->draw(text);
		windowRef->display();
	}

	textString = "loading: " + std::to_string(Loader::getInstance()->getPercentLoaded()) + "...";
	text.setString(textString);
	windowRef->clear();
	windowRef->draw(text);
	windowRef->display();
	windowRef->setActive(false);
}
