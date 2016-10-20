#pragma once
#include <vector>
#include <map>
#include <unordered_map>
#include "SFML/Graphics.hpp"
#include "SFML/Audio/Music.hpp"
#include "SFML/Audio/Sound.hpp"
#include "SFML\Audio.hpp"


class vsfuckerytest
{
public:
	vsfuckerytest(void);
	~vsfuckerytest(void);
	void fTest();
	std::map<std::string,sf::SoundBuffer> allSFXBuffers;
	std::map<std::string, sf::SoundBuffer> m_soundBuffers;
};

