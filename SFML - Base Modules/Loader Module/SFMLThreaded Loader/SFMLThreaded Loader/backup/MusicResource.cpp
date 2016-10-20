#include "MusicResource.h"

MusicResource::MusicResource(void)
{
	m_type = Resource::Resource_Type::Music;
}

MusicResource::~MusicResource(void)
{
	if(m_music)
	{
		m_music->stop();
		delete m_music;
	}
}

sf::Music* MusicResource::music()
{
	return m_music;
}