#pragma once
#include <string>
#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <ppl.h>
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include "SFML/Network/Http.hpp"
#include <list>
#include <sstream>
#include <vector>
#include <list>
#include "PlayerInformationSet.h"

using namespace std;

class httpCaller
{
public:
	httpCaller(void);
	~httpCaller(void);
	void caller();
	void RequestJSONValueAsync();
	list<PlayerInformationSet> getScoreBoard();
	void postToScoreBoard(PlayerInformationSet* p_playerInfo);
	bool checkConnected();
private:
	string getRawScoreboard();
	string httpAdress;
	bool m_connected;

};

