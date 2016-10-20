#include "MediaPack.h"


MediaPack::MediaPack(std::string name)
{
}

/*
MediaPack::~MediaPack(void)
{
}
/*
std::string MediaPack::name()
{
	return m_name;
}

	
void MediaPack::addTexture(std::string name, sf::Texture texture)
{
	m_textures[name] = texture;
}
	
sf::Texture* MediaPack::getTexture(std::string name)
{
	return &m_textures[name];
}
/*
void MediaPack::addSpritesheet(std::string name, sf::Texture texture, std::pair<int,int> rowsAndColumns)
{
	m_spritesheets[name] = std::pair<sf::Texture, std::pair<int,int>>(texture, rowsAndColumns);
}
/*	
sf::Texture* MediaPack::getSpritesheet(std::string name)
{
	//return &m_spritesheets[name].first;
	return new sf::Texture();
}
/*	
std::pair<int,int> MediaPack::getSpritesheetRowsAndColumns(std::string name)
{
	if(m_spritesheets.find(name) != m_spritesheets.end())
	//return m_spritesheets[name].second;
		return std::pair<int,int>(1,1);
}

//void MediaPack::addSoundBuffer(string name, sf::SoundBuffer soundBuffer)
//{
	//m_soundBuffers[name] = soundBuffer;
//}

//void MediaPack::addSoundBuffer(std::string name, sf::SoundBuffer sb)
//{

//}

sf::SoundBuffer* MediaPack::getSoundBuffer(std::string name)
{
	return &m_soundBuffers[name];
}

void MediaPack::addMusic(std::string name, sf::Music music)
{
	m_music[name] = music;
}

sf::Music* MediaPack::getMusic(std::string name)
{
	return &m_music[name];
}
*/