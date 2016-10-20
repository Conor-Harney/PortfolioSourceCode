#pragma once
#include "resource.h"
#include "SFML/Audio.hpp"
class SoundResource :
	public Resource
{
public:
	SoundResource(sf::Sound* sound, std::string name);
	~SoundResource(void);
	sf::Sound sound();

private:
	sf::SoundBuffer* m_SoundBuffer;
	sf::Sound* m_sound;
};

