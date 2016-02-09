#include "stdafx.h"
#include "Messanger.h"


Messanger::Messanger(const sf::Vector2f* screenSize, float* cameraSizeMultiplier, sf::Vector2f* cameraPosition):
	imageFadeOutTime(10), SCREENSIZE(screenSize), m_CameraPosition(cameraPosition)
{
	m_characterSize = 30;
	m_cameraSizeMultiplier = cameraSizeMultiplier;
	m_Font.loadFromFile("Media/Fonts/tahoma.ttf");
	m_Text.setFont(m_Font);
	m_Text.setCharacterSize(m_characterSize);
	m_Text.setColor(sf::Color::White);
	messageFadeOutTime = 0;
	messageAlpha = 0;
	
	m_ScoreText.setFont(m_Font);
	m_Text.setCharacterSize(m_characterSize);
	m_ScoreText.setColor(sf::Color::Yellow);
	m_ScoreText.setString("0:0");
	m_scoreBack.setFillColor(sf::Color::Blue);
}


Messanger::~Messanger(void)
{
}

void Messanger::displayMessage(string messageToDisplay){
	m_Text.setCharacterSize(m_characterSize * *m_cameraSizeMultiplier);
	messageAlpha = 255;
	messageFadeOutTime = messageToDisplay.size() / 20;
	if(messageFadeOutTime < 2){messageFadeOutTime = 2;}//minimum display: 2 seconds

	m_Text.setString(messageToDisplay);
	m_Text.setPosition(m_CameraPosition->x,m_CameraPosition->y + (SCREENSIZE->y * *m_cameraSizeMultiplier) - (m_Text.getGlobalBounds().height * 1.5));
	m_Text.setColor(sf::Color(0,0,0,messageAlpha));

	m_messageBack.setSize(sf::Vector2f(m_Text.getGlobalBounds().width, m_Text.getGlobalBounds().height + 20));
	m_messageBack.setPosition(m_Text.getPosition().x,m_Text.getPosition().y);
	m_messageBack.setFillColor(sf::Color(255,255,255, messageAlpha));
	AudioManager::getInstance()->playSoundEffect("messageSound");
}

void Messanger::displayInstantMessage(string messageToDisplay){
	m_Text.setCharacterSize(m_characterSize * *m_cameraSizeMultiplier);
	messageAlpha = 255;
	messageFadeOutTime = 0;

	m_Text.setString(messageToDisplay);
	m_Text.setPosition(m_CameraPosition->x,m_CameraPosition->y + (SCREENSIZE->y * *m_cameraSizeMultiplier) - (m_Text.getGlobalBounds().height * 1.5));
	m_Text.setColor(sf::Color(0,0,0,messageAlpha));

	m_messageBack.setSize(sf::Vector2f(m_Text.getGlobalBounds().width, m_Text.getGlobalBounds().height + 20));
	m_messageBack.setPosition(m_Text.getPosition().x,m_Text.getPosition().y);
	m_messageBack.setFillColor(sf::Color(255,255,255, messageAlpha));
	AudioManager::getInstance()->playSoundEffect("messageSound");
}

void Messanger::update(sf::Time timeElapsed, EnumStore::GAME_STATE* p_currentGameState){
	if(*p_currentGameState == EnumStore::GAME_STATE::IN_GAME){
		if(messageFadeOutTime <= 0 && messageAlpha > 0){
			messageFadeOutTime = 0;
			messageAlpha--;
			m_messageBack.setFillColor(sf::Color(0,0,0, messageAlpha));
			m_Text.setColor(sf::Color(255,255,255,messageAlpha));
		}
		else
		{
			messageFadeOutTime -= timeElapsed.asSeconds();

		}
		m_Text.setPosition(m_CameraPosition->x,m_CameraPosition->y + (SCREENSIZE->y * *m_cameraSizeMultiplier) - (m_Text.getGlobalBounds().height * 1.5));
		m_messageBack.setPosition(m_Text.getPosition().x,m_Text.getPosition().y);

		m_ScoreText.setPosition(m_CameraPosition->x + ((SCREENSIZE->x * *m_cameraSizeMultiplier) / 2),m_CameraPosition->y);
		m_ScoreText.setCharacterSize(m_characterSize * *m_cameraSizeMultiplier);
		
	}
	else if(*p_currentGameState == EnumStore::GAME_STATE::IN_INVENTORY)
	{
		m_ScoreText.setPosition(SCREENSIZE->x / 2,0);
		m_ScoreText.setCharacterSize(30);
	}
	m_scoreBack.setSize(sf::Vector2f(m_ScoreText.getGlobalBounds().width, m_ScoreText.getGlobalBounds().height * 1.5));
	m_scoreBack.setPosition(m_ScoreText.getPosition().x,m_ScoreText.getPosition().y);
}

void Messanger::Draw(sf::RenderWindow* window){
	window->draw(m_messageBack);
	window->draw(m_Text);
	window->draw(m_scoreBack);
	window->draw(m_ScoreText);
}

string Messanger::seperateStringLines(string linelessString, int stringWidth){

	string retString = "";
	list<string> words;

	int wordEndPos = linelessString.find(' ');

	while(linelessString.size() > 0){//break the string into words
		int breakPos = linelessString.find(' ');
		if(breakPos != -1){
			string word = linelessString.substr(0,breakPos + 1);
			words.push_front(word);
			linelessString.erase(0,breakPos + 1);
		}
		else{
			words.push_front(linelessString);
			linelessString.clear();
		}
	}

	//group the words into lines under the set size
	list<string> lines;
	sf::Text lineChecker;//used to check the size of the line
	sf::Font font;
	string lineString;
	if(font.loadFromFile("Media/Fonts/tahoma.ttf")){
		string oldString = "", newstring = "";

		lineChecker.setFont(font);
		lineChecker.setCharacterSize(m_characterSize);
		lineString = words.front();

		int wordsInString = 1;

		while(words.size() > 0){//group the words into the lines
			newstring.append(words.back());
			lineChecker.setString(newstring);

			if(lineChecker.getGlobalBounds().width > stringWidth){
				if(wordsInString > 1){
					oldString.append("\n");
					lines.push_front(oldString);
				}
				else{
					newstring.append("\n");
					lines.push_front(newstring);
					words.pop_back();
				}
				newstring = "";
				wordsInString = 0;
			}
			else{
				words.pop_back();
				wordsInString++;
			}
			oldString = newstring;

			if(words.size() == 0){
				lines.push_front(newstring);
			}

		}
		while(lines.size() > 0){
			retString.append(lines.back());
			lines.pop_back();
		}

	}
	return retString;
}

void Messanger::updateClock(std::pair<int, int> p_minsAndSeconds)
{
	string clockTime = " " + std::to_string(p_minsAndSeconds.first) + ":" + std::to_string(p_minsAndSeconds.second);
	m_ScoreText.setString(clockTime);
}