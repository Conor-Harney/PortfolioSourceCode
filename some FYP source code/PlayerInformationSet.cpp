#include "stdafx.h"
#include "PlayerInformationSet.h"

PlayerInformationSet::PlayerInformationSet()
{
}

PlayerInformationSet::PlayerInformationSet(int p_id, string p_name, int p_score):
	m_id(p_id), m_name(p_name), m_score(p_score)
{
}


PlayerInformationSet::~PlayerInformationSet(void)
{
}

int PlayerInformationSet::getId()
{
	return m_id;
}
	
string PlayerInformationSet::getName()
{
	return m_name;
}
	
int PlayerInformationSet::getScore()
{
	return m_score;
}

void PlayerInformationSet::setId(int p_id)
{
	m_id = p_id;
}

void PlayerInformationSet::setScore(int p_score)
{
	m_score = p_score;
}

void PlayerInformationSet::setName(string p_name)
{
	m_name = p_name;
}