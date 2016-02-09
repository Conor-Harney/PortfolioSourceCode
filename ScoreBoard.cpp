#include "stdafx.h"
#include "ScoreBoard.h"

ScoreBoard* ScoreBoard::m_insatnce;

ScoreBoard* ScoreBoard::getInstance()
{
	if(m_insatnce == 0)
	{
		m_insatnce = new ScoreBoard();
	}
	return m_insatnce;
}

ScoreBoard::ScoreBoard(void)
{
	scoreYPos[0] = 50;
	scoreYPos[1] = 150;
	scoreYPos[2] = 250;
	scoreYPos[3] = 350;
	scoreYPos[4] = 450;
	scoreXPos[0] = 50;//player place
	scoreXPos[1] = 200;//player score
	scoreXPos[2] = 400; //player name
	setUpText();
	m_currentPlayerInfoSet = new PlayerInformationSet(0,"",0);
	sortTopScoresWithoutCurrent();
	m_menuBackground = new sf::Sprite();
	ResourceManager::getInstance()->setUpSprite(m_menuBackground, "menuBackground", GlobalConstantsStore::getInsatnce()->getScreenDimensions());
}


ScoreBoard::~ScoreBoard(void)
{
}

void ScoreBoard::setUpText(){
	messageToDisplay = "";
	m_Font.loadFromFile("Media/Fonts/tahoma.ttf");
	m_Text.setFont(m_Font);
	m_Text.setCharacterSize(30);
	m_Text.setColor(sf::Color::White);
	m_Text.setString(messageToDisplay);
	m_Text.setPosition(sf::Vector2f(scoreXPos[0], scoreYPos[0]));
	m_Text.setColor(sf::Color(0,0,0,255));
}

void ScoreBoard::sortTopScoresWithCurrent()
{
	httpCaller caller;
	list<PlayerInformationSet> allPlayers = caller.getScoreBoard();
	if(allPlayers.size() > 0)
	{
		list<PlayerInformationSet> allPlayersTemp = allPlayers;
		map<int, PlayerInformationSet> bestPlayers;
		PlayerInformationSet lowestScore = PlayerInformationSet(0,"empty", -1);
		bestPlayers[1] = lowestScore;
		bestPlayers[2] = lowestScore;
		bestPlayers[3] = lowestScore;
		bestPlayers[4] = lowestScore;
		bestPlayers[5] = lowestScore;
		list<int> allScores;
		while(allPlayersTemp.size() > 0)
		{
			if(allPlayersTemp.back().getScore() >= bestPlayers[1].getScore())
			{//current back is best player
				bestPlayers[5] = bestPlayers[4];
				bestPlayers[4] = bestPlayers[3];
				bestPlayers[3] = bestPlayers[2];
				bestPlayers[2] = bestPlayers[1];
				bestPlayers[1] = allPlayersTemp.back();

			}
			else if(allPlayersTemp.back().getScore() >= bestPlayers[2].getScore())
			{//current back is 2nd best player
				bestPlayers[5] = bestPlayers[4];
				bestPlayers[4] = bestPlayers[3];
				bestPlayers[3] = bestPlayers[2];
				bestPlayers[2] = allPlayersTemp.back();

			}
			else if(allPlayersTemp.back().getScore() >= bestPlayers[3].getScore())
			{//current back is 3rd best player
				bestPlayers[5] = bestPlayers[4];
				bestPlayers[4] = bestPlayers[3];
				bestPlayers[3] = allPlayersTemp.back();

			}
			else if(allPlayersTemp.back().getScore() >= bestPlayers[4].getScore())
			{//current back is best player
				bestPlayers[5] = bestPlayers[4];
				bestPlayers[4] = allPlayersTemp.back();

			}
			else if(allPlayersTemp.back().getScore() >= bestPlayers[4].getScore())
			{//current back is best player
				bestPlayers[5] = allPlayersTemp.back();

			}
			allScores.push_back(allPlayersTemp.back().getScore());
			allPlayersTemp.pop_back();
		}
		allScores.sort();
		allScores.unique();
		int curPID = m_currentPlayerInfoSet->getId();
		//always keep player on scoreboard with top 4 players
		rankToBestPlayers.clear();
		rankToBestPlayers.push_back(pair<int, PlayerInformationSet>(1, bestPlayers[1]));
		rankToBestPlayers.push_back(pair<int, PlayerInformationSet>(2, bestPlayers[2]));
		rankToBestPlayers.push_back(pair<int, PlayerInformationSet>(3, bestPlayers[3]));
		rankToBestPlayers.push_back(pair<int, PlayerInformationSet>(4, bestPlayers[4]));
		if(bestPlayers[1].getId() == curPID ||
			bestPlayers[2].getId() == curPID||
			bestPlayers[3].getId() == curPID||
			bestPlayers[4].getId() == curPID||
			bestPlayers[5].getId() == curPID)
		{
			//if player is in top 5, all ranks are correct
			rankToBestPlayers.push_back(pair<int, PlayerInformationSet>(5, bestPlayers[5]));
		}
		else
		{
			int playerRank = 1;
			bool found = false;
			for(int curRank = 1; found == false; curRank++)
			{//itterate through all the scores untill you find the players rank 
				if (allScores.back() == m_currentPlayerInfoSet->getScore())
				{
					playerRank = curRank;
					found = true;
				}
				allScores.pop_back();
			}
			rankToBestPlayers.push_back(pair<int, PlayerInformationSet>(playerRank, *m_currentPlayerInfoSet));
		}
	}
}

void ScoreBoard::setMyScore(PlayerInformationSet p_playerInfo)
{
	*m_currentPlayerInfoSet = p_playerInfo;
	httpCaller caller;
	caller.postToScoreBoard(m_currentPlayerInfoSet);
	sortTopScoresWithCurrent();
}

void ScoreBoard::renderScoreboard()
{
	if(rankToBestPlayers.size() != 0)
	{
		ResourceManager::getInstance()->getRenderer()->draw(*m_menuBackground);
		list<pair<int, PlayerInformationSet>> temptopRanksToPlayers = rankToBestPlayers;
		for(int i = 0; temptopRanksToPlayers.size() > 0; i++)
		{
			string output = "rank: ";
			output.append(std::to_string(temptopRanksToPlayers.front().first));
			m_Text.setString(output);
			m_Text.setPosition(sf::Vector2f(scoreXPos[0], scoreYPos[i]));
			ResourceManager::getInstance()->getRenderer()->draw(m_Text);
			output = "Score: ";
			output.append(std::to_string(temptopRanksToPlayers.front().second.getScore()));
			m_Text.setString(output);
			m_Text.setPosition(sf::Vector2f(scoreXPos[1], scoreYPos[i]));
			ResourceManager::getInstance()->getRenderer()->draw(m_Text);
			output = "Name: ";
			output.append(temptopRanksToPlayers.front().second.getName());
			m_Text.setString(output);
			m_Text.setPosition(sf::Vector2f(scoreXPos[2], scoreYPos[i]));
			ResourceManager::getInstance()->getRenderer()->draw(m_Text);
			temptopRanksToPlayers.pop_front();
		}
	}
}

void ScoreBoard::sortTopScoresWithoutCurrent()
{
	httpCaller caller;
	list<PlayerInformationSet> allPlayers = caller.getScoreBoard();
	
	map<int, PlayerInformationSet> bestPlayers;
	PlayerInformationSet lowestScore = PlayerInformationSet(0,"empty", -1);
	bestPlayers[1] = lowestScore;
	bestPlayers[2] = lowestScore;
	bestPlayers[3] = lowestScore;
	bestPlayers[4] = lowestScore;
	bestPlayers[5] = lowestScore;
	
	if(allPlayers.size() > 0)
	{
		list<PlayerInformationSet> allPlayersTemp = allPlayers;
		while(allPlayersTemp.size() > 0)
		{
			if(allPlayersTemp.back().getScore() >= bestPlayers[1].getScore())
			{//current back is best player
				bestPlayers[5] = bestPlayers[4];
				bestPlayers[4] = bestPlayers[3];
				bestPlayers[3] = bestPlayers[2];
				bestPlayers[2] = bestPlayers[1];
				bestPlayers[1] = allPlayersTemp.back();

			}
			else if(allPlayersTemp.back().getScore() >= bestPlayers[2].getScore())
			{//current back is 2nd best player
				bestPlayers[5] = bestPlayers[4];
				bestPlayers[4] = bestPlayers[3];
				bestPlayers[3] = bestPlayers[2];
				bestPlayers[2] = allPlayersTemp.back();

			}
			else if(allPlayersTemp.back().getScore() >= bestPlayers[3].getScore())
			{//current back is 3rd best player
				bestPlayers[5] = bestPlayers[4];
				bestPlayers[4] = bestPlayers[3];
				bestPlayers[3] = allPlayersTemp.back();

			}
			else if(allPlayersTemp.back().getScore() >= bestPlayers[4].getScore())
			{//current back is best player
				bestPlayers[5] = bestPlayers[4];
				bestPlayers[4] = allPlayersTemp.back();

			}
			else if(allPlayersTemp.back().getScore() >= bestPlayers[5].getScore())
			{//current back is best player
				bestPlayers[5] = allPlayersTemp.back();

			}
			allPlayersTemp.pop_back();
		}
	}
	rankToBestPlayers.clear();
	rankToBestPlayers.push_back(pair<int, PlayerInformationSet>(1, bestPlayers[1]));
	rankToBestPlayers.push_back(pair<int, PlayerInformationSet>(2, bestPlayers[2]));
	rankToBestPlayers.push_back(pair<int, PlayerInformationSet>(3, bestPlayers[3]));
	rankToBestPlayers.push_back(pair<int, PlayerInformationSet>(4, bestPlayers[4]));
	rankToBestPlayers.push_back(pair<int, PlayerInformationSet>(5, bestPlayers[5]));
	
}