#include "SoundResource.h"


SoundResource::SoundResource(sf::Sound* sound, std::string name)
{
	m_type = Sound;
	m_name = name;
}


SoundResource::~SoundResource(void)
{
	if(m_sound)
	{
		m_sound->stop();
		delete m_sound;
	}
	if(m_SoundBuffer)
		delete m_SoundBuffer;

}

sf::Sound SoundResource::sound()
{
	return *m_sound;
}