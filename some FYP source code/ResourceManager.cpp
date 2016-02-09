#include "stdafx.h"
#include "ResourceManager.h"

//To load a new file:
//Add the file name to the appropriate list in setMediaToLoad()
//sound effect files go in "./Media/Audio/sfx" folder (.wav only)
//Music files go in "./Media/Audio/Music" folder (.ogg only)
//Image files go in the images sub folder (.png only)

ResourceManager* ResourceManager::m_instance = 0;

ResourceManager::ResourceManager(void)
{
	m_renderer = NULL;
}

ResourceManager::~ResourceManager(void)
{
}

sf::RenderWindow* ResourceManager::getRenderer()
{
	return m_renderer;
}

ResourceManager* ResourceManager::getInstance(){
	if(0 == m_instance)
	{
		m_instance = new ResourceManager();
	}
	return m_instance;
}

bool ResourceManager::loadAllMedia()
{
	bool mediaLoaded = false;
	if(m_renderer)
	{//init needs to be called first
		if(loadSfx() && loadImages() && loadMusic())
		{
			mediaLoaded = true;
		}
	}
	return mediaLoaded;
}

void ResourceManager::init(sf::RenderWindow* p_renderer){
	if(!m_renderer)
	{
		m_renderer = p_renderer;
		setMediaToLoad();
		loadAllMedia();
	}
}

bool ResourceManager::loadSfx()
{//auto load all files in the sfx folder
	bool allLoaded = true;
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir ("./Media/Audio/sfx")) != NULL) {

		/* print all the files and directories within directory */
		for(int i = 0; (ent = readdir (dir)) != NULL; i++){
			if(i != 0 && i!= 1){
				string dirName = "Media/Audio/Sfx/";
				dirName.append(ent->d_name);
				if (!allSFXBuffers[dirName].loadFromFile(dirName)){
					allLoaded = false;
				}
				else
				{
					m_sfxNames.push_back(ent->d_name);
					m_sfxMap[ent->d_name] = new sf::Sound();
					m_sfxMap[ent->d_name]->setBuffer(allSFXBuffers[dirName]);
				}
			}
		}
		closedir (dir);
	} 
	else {
		/* could not open directory */
		perror ("");
		allLoaded = false;
	}
	return allLoaded;
}

bool ResourceManager::loadMusic()
{//load all audio files
	bool allLoaded = true;
	string baseDidectory = "Media/Audio/Music/Track";
	string extension = ".ogg";

	if (!track1.openFromFile(baseDidectory + "1" + extension))
	{
		allLoaded = false;
	}
	else
	{
		m_musicMap["Track1"] = &track1;
		m_musicNames.push_back("Track1");
	}
	if (!track2.openFromFile(baseDidectory + "2" + extension))
	{
		allLoaded = false;
	}
	else
	{
		m_musicMap["Track2"] = &track2;
		m_musicNames.push_back("Track2");
	}
	if (!track3.openFromFile(baseDidectory + "3" + extension))
	{
		allLoaded = false;
	}
	else
	{
		m_musicMap["Track3"] = &track3;
		m_musicNames.push_back("Track3");
	}
	/*if (!track4.openFromFile(baseDidectory + "4" + extension)){
		allLoaded = false;
	}
	if (!track5.openFromFile(baseDidectory + "5" + extension)){
		allLoaded = false;
	}*/
	return allLoaded;
}

bool ResourceManager::loadImages()
{//loads all image files in the setMediaToLoad method
	bool mediaLoaded = true;
	for (int i = 0; i < m_imageNames.size(); i++)
	{
		std::string pathStr = "Media/Images/" + m_imageNames.at(i) + ".png";
		const char* pathChar = pathStr.c_str();
		m_textureMap[m_imageNames.at(i)] = new sf::Texture();
		if(!m_textureMap[m_imageNames.at(i)]->loadFromFile(pathChar))
		{
			mediaLoaded = false;
		}
		else
		{
			setFrameVars(m_imageNames.at(i));
		}
	}
	return mediaLoaded;
}

void ResourceManager::updateSpriteFrame(sf::Sprite* p_sprite, string p_imageName, unsigned int p_column, unsigned int p_row)
{
	sf::IntRect curRect;
	curRect.left = p_column * m_sourecAnimFrameDimensions[p_imageName]->x;
	curRect.top = p_row * m_sourecAnimFrameDimensions[p_imageName]->y;
	curRect.width = m_sourecAnimFrameDimensions[p_imageName]->x;
	curRect.height = m_sourecAnimFrameDimensions[p_imageName]->y;
	p_sprite->setTextureRect(curRect);
}

void ResourceManager::setMediaToLoad()
{//add the files with these names
	//images (.png only!)
	//addImage("blankImage", 1);
	addImage("PlayerSpriteSheet1", sf::Vector2i(4,3));
	addImage("menuBackground", sf::Vector2i(1,1));
	addImage("newGameButton", sf::Vector2i(1,1));
	addImage("continueButton", sf::Vector2i(1,1));
	addImage("muteButton", sf::Vector2i(1,1));
	addImage("scoreboardButton", sf::Vector2i(1,1));
	addImage("buttonHighlite", sf::Vector2i(1,1));
	addImage("tutorialImage", sf::Vector2i(1,1));
	addImage("tutorialButton", sf::Vector2i(1,1));
	addImage("enterName", sf::Vector2i(1,1));
}

bool ResourceManager::checkSfxExists(std::string p_audioName)
{//p_audioName should contain file extention
	bool exists = false;
	vector<string>::iterator sfxItter;

	for(sfxItter = m_sfxNames.begin(); sfxItter < m_sfxNames.end(); sfxItter++)
	{
		if(*sfxItter == p_audioName)
		{
			exists = true;
			break;
		}
	}
	return true;
}

sf::Sound* ResourceManager::getSfx(std::string p_audioName)
{//p_audioName should contain file extention
	return m_sfxMap[p_audioName];
}

bool ResourceManager::checkMusicExists(std::string p_audioName)
{//p_audioName should not contain file extention
	bool exists = false;
	vector<string>::iterator musicItter;

	for(musicItter = m_musicNames.begin(); musicItter < m_musicNames.end(); musicItter++)
	{
		if(*musicItter == p_audioName)
		{
			exists = true;
			break;
		}
	}
	return exists;
}

sf::Music* ResourceManager::getMusic(std::string p_audioName)
{//p_audioName not contain file extention
	return m_musicMap[p_audioName];
}

bool ResourceManager::checkTextureExists(string p_textureName)
{
	bool exists = false;
	vector<string>::iterator textureItter;

	for(textureItter = m_imageNames.begin(); textureItter < m_imageNames.end(); textureItter++)
	{
		if(*textureItter == p_textureName)
		{
			exists = true;
			break;
		}
	}
	return true;
}

sf::Texture* ResourceManager::getTexture(std::string p_imageName)
{//p_imageName should not contain file extention
	bool imageFound = false;
	for(int i =0; i < m_imageNames.size(); i++){
		if(p_imageName == m_imageNames.at(i))
		{
			imageFound = true;
			return m_textureMap[p_imageName];
		}
	}
	return m_textureMap["default"];
}

void ResourceManager::drawImage(sf::Sprite* p_sprite, string p_imageName, sf::Vector2u p_columnAndRow)
{
	m_renderer->draw(*p_sprite);
}

void ResourceManager::setFrameVars(std::string p_imageName)
{
	//called internaly from loadImages()
	int w = m_textureMap[p_imageName]->getSize().x;
	int h = m_textureMap[p_imageName]->getSize().y;
	m_sourecAnimFrameDimensions[p_imageName] = (new sf::Vector2u());
	m_sourecAnimFrameDimensions[p_imageName]->x = (w/m_ColumnsAndRows[p_imageName].x);
	m_sourecAnimFrameDimensions[p_imageName]->y = (h/m_ColumnsAndRows[p_imageName].y);
}

int ResourceManager::getAnimationFrames(std::string p_imageName)
{
	return m_ColumnsAndRows[p_imageName].x;
}

void ResourceManager::addImage(std::string p_imageName, sf::Vector2i p_numOfColumns)
{
	///adds an image to load
	///param[p_imageName] the name of the image to add
	///param[p_numOfColumns] the number of columns in the spritesheet
	m_imageNames.push_back(p_imageName);
	m_ColumnsAndRows[p_imageName] = p_numOfColumns;
}

bool ResourceManager::checkImageLoaded(std::string p_imageName)
{
	bool isImageLoaded = false;
	for(int i = 0; i < m_imageNames.size(); i++)
	{
		if(m_imageNames.at(i) == p_imageName)
		{
			isImageLoaded = true;
			break;
		}
	}
	return isImageLoaded;
}

void ResourceManager::setUpSprite(sf::Sprite* p_sprite, string p_imageName, sf::Vector2f p_size)
{
	//sets up a sprite to be used with the resource loader
	//Do not call "new sf::Sprite()" here!
	//It will lose value as soon as it exits the method
	p_sprite->setTexture(*m_textureMap[p_imageName]);
	p_sprite->setTextureRect(sf::IntRect(0,0, 
		m_sourecAnimFrameDimensions[p_imageName]->x, m_sourecAnimFrameDimensions[p_imageName]->y));
	p_sprite->setScale(p_size.x / m_sourecAnimFrameDimensions[p_imageName]->x, 
		p_size.y / m_sourecAnimFrameDimensions[p_imageName]->y);
	p_sprite->setPosition(0,0);
}