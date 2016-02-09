#pragma once
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include "SFML/Audio.hpp"
#include <string>
#include <memory.h>
#include <list>
#include <Map>
#include "dirent.h"

using namespace std;

class ResourceManager
{
public:
	static ResourceManager* m_instance;
	static ResourceManager* getInstance();
	bool loadAllMedia();
	//SDL_Texture* getImage(EnumHolder::ImageNames p_name);
	void init(sf::RenderWindow* p_renderer);
	bool checkSfxExists(std::string p_audioName);
	sf::Sound* getSfx(std::string p_audioName);
	bool checkMusicExists(std::string p_audioName);
	sf::Music* getMusic(std::string p_audioName);
	bool checkTextureExists(std::string p_imageName);
	sf::Texture* getTexture(std::string p_imageName);
	void drawImage(sf::Sprite* p_sprite, string p_imageName, sf::Vector2u p_columnAndRow); 
	sf::RenderWindow* getRenderer();
	int getAnimationFrames(std::string p_imageName);
	void updateSpriteFrame(sf::Sprite* p_sprite, string p_imageName, unsigned int p_column, unsigned int p_row);
	void setUpSprite(sf::Sprite* p_sprite, string p_imageName, sf::Vector2f p_size);
	
private:
	ResourceManager(void);
	~ResourceManager(void);
	bool loadSfx();
	bool loadMusic();
	bool loadImages();
	sf::RenderWindow* m_renderer;
	void setMediaToLoad();
	void setFrameVars(std::string p_imageName);
	void addImage(std::string p_imageName, sf::Vector2i p_columnsRows);
	bool checkImageLoaded(std::string p_imageName);
	
	std::map<std::string, sf::Texture*> m_textureMap;
	std::vector<std::string> m_imageNames;
	std::map<std::string, sf::Vector2i> m_ColumnsAndRows;
	std::map<std::string, sf::Vector2u*> m_sourecAnimFrameDimensions;


	map<string,sf::SoundBuffer> allSFXBuffers;
	std::map<std::string, sf::Sound*> m_sfxMap;
	std::vector<std::string> m_sfxNames;

	std::map<std::string, sf::Music*> m_musicMap;
	std::vector<std::string> m_musicNames;

	//sf::music cannot be stored in a container
	sf::Music track1;
	sf::Music track2;
	sf::Music track3;
	sf::Music track4;
	sf::Music track5;
};

