#pragma once
#include <vector>
#include <map>
#include <unordered_map>
#include "SFML/Graphics.hpp"
#include "SFML/Audio/Music.hpp"
#include "SFML/Audio/Sound.hpp"
#include "SFML\Audio.hpp"


class testEnv
{
public:
	testEnv(void);
	~testEnv(void);
	void fTest();
	std::map<std::string, sf::Music*> m_musics;
};

