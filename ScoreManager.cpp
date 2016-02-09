#include "stdafx.h"
#include "ScoreManager.h"

ScoreManager* ScoreManager::m_instance;

ScoreManager* ScoreManager::getInstance()
{
	if(m_instance == NULL)
	{
		m_instance = new ScoreManager();
	}
	return m_instance;
}

ScoreManager::ScoreManager(void)
{
	m_currentLevelTime = 0;
	m_currentLevelPickupScore = 0;
	m_levelToMaxTimeAndPickupScore[0] = std::pair<int,int>(15, 50);
	m_levelToMaxTimeAndPickupScore[1] = std::pair<int,int>(15, 30);
	m_levelToMaxTimeAndPickupScore[2] = std::pair<int,int>(15, 30);
	m_levelToMaxTimeAndPickupScore[3] = std::pair<int,int>(15, 30);
}


ScoreManager::~ScoreManager(void)
{
}

int ScoreManager::calculateLevelScore(float levelParTime, int possibleItemScore)
{//1000 is max score for a level
	float pickupScore = getCurrentPickupScore();
	float levelScore = (pickupScore / possibleItemScore) * 500;//500 points possible for pickups.
	//0 for time is 9 times the par (levelParTime * 9) 
	float timeOverPar = m_currentLevelTime - levelParTime;
	float timeScore;//500 points possible for time
	if(timeOverPar < 0)
	{
		timeOverPar = 0; 
		timeScore = 500;
	}
	else
	{
		if(timeOverPar > (levelParTime * 8))
		{
			timeOverPar = (levelParTime * 8);
		}
		timeScore = 500 - ((timeOverPar / (levelParTime * 8)) * 500);
	}

	levelScore += timeScore;
	int truncatedScore = levelScore;
	return truncatedScore;
}

void ScoreManager::addToTotalScore(int p_scoreToAdd)
{
	m_totalScore += p_scoreToAdd;
}

int ScoreManager::getTotalScore()
{
	return m_totalScore;
}
	
void ScoreManager::addToScore(int p_scoreToAdd)
{
	m_currentLevelPickupScore += p_scoreToAdd;
}

void ScoreManager::updateTime(sf::Time timeElasped)
{
	m_currentLevelTime += timeElasped.asSeconds();
}

std::pair<int, float> ScoreManager::getCurrentLevelTime()
{// minutes & seconds
	std::pair<int, float> curTime = std::pair<int, float>(0,m_currentLevelTime);
	float seconds = m_currentLevelTime;
	while(seconds > 60.0)
	{
		curTime.first = curTime.first + 1;
		seconds -= 60;
	}
	curTime.second = seconds;
	return curTime;
}

int ScoreManager::getCurrentPickupScore()
{
	return m_currentLevelPickupScore;
}

void ScoreManager::resetCounters()
{
	m_currentLevelTime = 0;
	m_currentLevelPickupScore = 0;
}

void ScoreManager::init(Messanger* p_messanger)
{
	m_messanger = p_messanger;
}

void ScoreManager::nextLevel(int p_levelPassed)
{
	//save data to level set
	m_levelToScore[p_levelPassed] = calculateLevelScore(m_levelToMaxTimeAndPickupScore[p_levelPassed].first,m_levelToMaxTimeAndPickupScore[p_levelPassed].second);
	addToTotalScore(m_levelToScore[p_levelPassed]);
	resetCounters();
}

void ScoreManager::clearScore()
{
	m_totalScore = 0;
}