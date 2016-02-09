#pragma once
#include "PlayerInformationSet.h"
#include <vector>
#include "SFML/Graphics.hpp" 
#include "httpCaller.h"
#include <map>
#include <list>
#include <iostream>
#include "ResourceManager.h"
#include "GlobalConstantsStore.h"

using namespace std;
//manages the scoreboard page that appears at the end of the game 
//and when the player choses to view the scoreboard
class ScoreBoard
{
public:
	static ScoreBoard* m_insatnce;
	static ScoreBoard* getInstance();
	void setScores();
	void setMyScore(PlayerInformationSet p_playerInfo);
	void renderScoreboard();
	void sortTopScoresWithoutCurrent();

private:
	ScoreBoard(void);
	~ScoreBoard(void);
	void sortTopScoresWithCurrent();
	float scoreYPos[5];
	float scoreXPos[3];
	void setUpText();
	sf::Font m_Font;
	sf::Text m_Text;
	string messageToDisplay;
	PlayerInformationSet* m_currentPlayerInfoSet;
	list<pair<int, PlayerInformationSet>> rankToBestPlayers;
	sf::Sprite* m_menuBackground;

};

