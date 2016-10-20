#include "MediaPack.h"


MediaPack::MediaPack(std::string name)
{
}


MediaPack::~MediaPack(void)
{
}

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

void MediaPack::addSpritesheet(std::string name, sf::Texture texture, std::pair<int,int> rowsAndColumns)
{
	m_spritesheets[name] = std::pair<sf::Texture, std::pair<int,int>>(texture, rowsAndColumns);
}

sf::Texture* MediaPack::getSpritesheet(std::string name)
{
	return &m_spritesheets[name].first;
}

std::pair<int,int> MediaPack::getSpritesheetRowsAndColumns(std::string name)
{
	if(m_spritesheets.find(name) != m_spritesheets.end())
		return m_spritesheets[name].second;
	else
		return std::pair<int,int>(1,1);
}

void MediaPack::addSoundBuffer(std::string name, sf::SoundBuffer soundBuffer)
{
	m_soundBuffers[name] = soundBuffer;
}

sf::SoundBuffer* MediaPack::getSoundBuffer(std::string name)
{
	return &m_soundBuffers[name];
}

sf::Music* MediaPack::getMusic(std::string name)
{
	if(m_music.find(name) == m_music.end())
		m_music[name] = new sf::Music();
	
	return m_music[name];
}