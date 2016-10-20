#pragma once
#include <vector>
#include <map>
#include <unordered_map>
#include "SFML/Graphics.hpp"
#include "SFML/Audio/Music.hpp"
#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"
#include "SFML\Audio.hpp"

class MediaPack
{
	//This represents a folder of sounds, music, images and spritesheets
	//packs will be dynamically loaded and unloaded at run time 
private:
	//each map has a name and an element
	std::unordered_map<std::string, sf::Texture> m_textures;
	std::unordered_map<std::string, std::pair<sf::Texture, std::pair<int,int>>> m_spritesheets;//the spritesheet , and the rows and columns
	std::map<std::string, sf::SoundBuffer> m_soundBuffers;
	std::unordered_map<std::string, sf::Music*> m_music;//to add a music track, use this getMusic(name)->openFromFile()
	std::string m_name;
public:
	MediaPack(std::string name);
	~MediaPack(void);
	
	std::string name();

	void addTexture(std::string name, sf::Texture texture);
	sf::Texture* getTexture(std::string name);

	void addSpritesheet(std::string name, sf::Texture texture, std::pair<int,int> rowsAndColumns);
	sf::Texture* getSpritesheet(std::string name);
	std::pair<int,int> getSpritesheetRowsAndColumns(std::string name);

	void addSoundBuffer(std::string name, sf::SoundBuffer soundBuffer);
	sf::SoundBuffer* getSoundBuffer(std::string name);

	sf::Music* getMusic(std::string name);


};
