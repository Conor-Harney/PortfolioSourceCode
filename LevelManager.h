#pragma once
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <list>
#include <vector>
#include <map>
#include "FlipSwitch.h"
#include "EnvirementItem.h"
#include "MapLoader.h"
#include <future>
#include <thread>

class LevelManager
{
public:
	LevelManager(const sf::Vector2f* screenDimentions);
	~LevelManager(void);
	void renderLevel(sf::RenderWindow* window);
	void buildLevel(float levelNumAndScene);
	float getFloorLevel(sf::Vector2f topLeftPos, sf::Vector2f dimentions);
	float getRoofLevel(sf::Vector2f topLeftPos, sf::Vector2f dimentions);
	float getWallLeft(sf::Vector2f topLeftPos, sf::Vector2f dimentions);
	float getWallRight(sf::Vector2f topLeftPos, sf::Vector2f dimentions);
	void buildTiledLevel(int p_room, bool* isDone);
	void buildTiledLevel(int p_room);
	void drawAllTiles(sf::RenderWindow* window);
	const sf::Vector2f SCREEN_CELL_SIZE;//the screen will be devided into a 10 by 10 grid
	void setLevelSet(int levelSet);
	int getLevelSet();
	int getCurrentRoom();

private:
	std::list<sf::FloatRect>* wallList;
	std::list<sf::FloatRect>* platformList;
	std::list<std::pair<std::string, sf::FloatRect>>* envirementItemList;
	void addEnvirementItem(float left, float top, float width, float height, std::string itemName);
	void addPlatform(int gridXLeft, int gridYTop, int gridWidth); 
	void addWall(int gridXLeft, int gridYTop, int gridHeight); 
	std::map<int, std::map<int, char>> gridMap;
	void populateMap();
	std::list<EnvirementItem>* itemList;
	MapLoader m_mapLoader;
	sf::FloatRect getDrawRect(int gridPosX, int intgridPosY);
	bool LevelManager::loadMedia();
	sf::Sprite m_levelTextureSprite;
	sf::Texture m_levelTexture;
	sf::Vector2i SSImageSize;
	const int FRAMES_PER_ROW;
	const int SPRITE_SHEET_ROWS;
	void addTile(int gridx, int gridy, int layer, int tileValue);
	list<sf::Sprite> tileSpritesList;
	void clearLevel();

	int m_LevelSet;//current set of levels
	int m_currentRoom;
};

