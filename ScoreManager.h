#pragma once
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp"
#include "Messanger.h"

class ScoreManager
{
public:
	static ScoreManager* getInstance();
	void init(Messanger* p_messanger);
	int calculateLevelScore(float levelParTime, int possibleItemScore);
	void addToScore(int p_scoreToAdd);
	void updateTime(sf::Time timeElasped);
	std::pair<int, float> getCurrentLevelTime();
	int getCurrentPickupScore();
	void resetCounters();
	void nextLevel(int p_levelPassed);
	std::map<int, std::pair<int,int>> m_levelToMaxTimeAndPickupScore;
	void addToTotalScore(int p_scoreToAdd);
	int getTotalScore();
	void clearScore();

private:
	float m_currentLevelTime;
	int m_currentLevelPickupScore;
	static ScoreManager* m_instance;
	ScoreManager(void);
	~ScoreManager(void);
	Messanger* m_messanger;
	std::map<int, int> m_levelToScore;
	int m_totalScore;
};

