#pragma once
#include <string>
//stores a players information
using namespace std;
class PlayerInformationSet
{
public:
	PlayerInformationSet();
	PlayerInformationSet(int p_id, string p_name, int p_score);
	~PlayerInformationSet(void);
	int getId();
	string getName();
	void setName(string p_name);
	int getScore();
	void setScore(int p_score);
	void setId(int p_id);

private:
	int m_id;
	string m_name;
	int m_score;
};

