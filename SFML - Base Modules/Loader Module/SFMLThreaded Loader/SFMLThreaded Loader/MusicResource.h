#pragma once
#include "resource.h"
#include "SFML/Audio.hpp"
class MusicResource : public Resource
{
public:
	MusicResource(void);
	~MusicResource(void);
	sf::Music* music();//returns a pointer so the music can be paused/stopped etc.

private:
	sf::Music* m_music;
};

