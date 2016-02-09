#include "stdafx.h"
#include "LevelManager.h"

LevelManager::LevelManager(const sf::Vector2f* screenDimentions): SCREEN_CELL_SIZE(screenDimentions->x / 10, screenDimentions->y / 10), FRAMES_PER_ROW(10), SPRITE_SHEET_ROWS(10)
{
	wallList = new std::list<sf::FloatRect>();
	platformList = new std::list<sf::FloatRect>;
	envirementItemList = new std::list<std::pair<std::string, sf::FloatRect>>;
	itemList = new std::list<EnvirementItem>;
	m_mapLoader = MapLoader();
	loadMedia();
	m_LevelSet = 0;
	int m_currentRoom = 1;
}

LevelManager::~LevelManager(void)
{
}

sf::FloatRect LevelManager::getDrawRect(int gridPosX, int intgridPosY){
	return sf::FloatRect(SCREEN_CELL_SIZE.x * gridPosX, SCREEN_CELL_SIZE.y *  gridPosX, SCREEN_CELL_SIZE.x, SCREEN_CELL_SIZE.y);
}

/*{0-9, 0-9, 1-10, 1-10} */
void LevelManager::addPlatform(int gridXLeft, int gridYTop, int gridWidth){
	platformList->push_back(sf::FloatRect(SCREEN_CELL_SIZE.x * gridXLeft, SCREEN_CELL_SIZE.y *  gridYTop, SCREEN_CELL_SIZE.x * gridWidth, SCREEN_CELL_SIZE.y));
}

void LevelManager::addWall(int gridXLeft, int gridYTop, int gridHeight){
	wallList->push_back(sf::FloatRect(SCREEN_CELL_SIZE.x * gridXLeft, SCREEN_CELL_SIZE.y *  gridYTop, SCREEN_CELL_SIZE.x , SCREEN_CELL_SIZE.y * gridHeight));
}

void LevelManager::addEnvirementItem(float left, float top, float width, float height, std::string itemName){
	sf::FloatRect rect(SCREEN_CELL_SIZE.x * left, SCREEN_CELL_SIZE.y * top, width, height);
	std::pair<std::string, sf::FloatRect> itemPair(itemName, rect);
	envirementItemList->push_back(itemPair);

	if(itemName == "FlipSwitch"){
		itemList->push_back(FlipSwitch(sf::Vector2f(SCREEN_CELL_SIZE.x * left,SCREEN_CELL_SIZE.y * top),1));
	}
}

void LevelManager::renderLevel(sf::RenderWindow* window){
	//render walls
	std::list<sf::FloatRect> tempWallList = *wallList;
	for(int i = 0; i < wallList->size(); i++){
		sf::FloatRect currWallRec = tempWallList.front();
		sf::RectangleShape tempWallShape;
		tempWallShape.setSize(sf::Vector2f(currWallRec.width, currWallRec.height));
		tempWallShape.setPosition(currWallRec.left, currWallRec.top);
		window->draw(tempWallShape);
		tempWallList.pop_front();
	}

	//render platforms
	std::list<sf::FloatRect> tempPlatformList = *platformList;
	for(int i = 0; i < platformList->size(); i++){
		sf::FloatRect currPlatformRec = tempPlatformList.front();
		sf::RectangleShape tempPlatformShape;
		tempPlatformShape.setSize(sf::Vector2f(currPlatformRec.width, currPlatformRec.height));
		tempPlatformShape.setPosition(currPlatformRec.left, currPlatformRec.top);
		tempPlatformShape.setFillColor(sf::Color(100,0,0));
		window->draw(tempPlatformShape);
		tempPlatformList.pop_front();
	}

}

void LevelManager::buildLevel(float levelNumAndScene){
	//Read from a text file
	//Each character represents a cell
	//the final line represents the background image
	populateMap();

	for(int y = 0; y < gridMap.size(); y++)
	{
		std::map<int, char> xMap = gridMap[y];
		for(int x = 0; x < xMap.size(); x++)
		{
			char cellCharacter = xMap[x];

			switch(cellCharacter){
			case 'p':
				addPlatform(x, y, 1);
				break;
			case 's':
				addEnvirementItem(x,y,0,0,"FlipSwitch");
			default:
				break;
			}

		}

	}
}

float LevelManager::getFloorLevel(sf::Vector2f topLeftPos, sf::Vector2f dimentions){
	//convert to a grid position
	float closestPlatformY = SCREEN_CELL_SIZE.y * 10;//full screen size
	std::list<sf::FloatRect> tempPlatList = *platformList;//list of platforms to pop

	for(int i = 0; i < platformList->size(); i++){
		sf::FloatRect currRect = tempPlatList.front();
		//int recY = currRect.top;
		if (currRect.top >= (topLeftPos.y + dimentions.y)){
			if(currRect.left < (topLeftPos.x + dimentions.x) && (currRect.left + currRect.width) > topLeftPos.x){
				if(currRect.top < closestPlatformY){
					closestPlatformY = currRect.top;
				}
			}
		}
		tempPlatList.pop_front();
	}

	return closestPlatformY;
}

float LevelManager::getRoofLevel(sf::Vector2f topLeftPos, sf::Vector2f dimentions){
	//convert to a grid position
	float closestPlatformY = 0;
	std::list<sf::FloatRect> tempPlatList = *platformList;//list of platforms to pop

	for(int i = 0; i < platformList->size(); i++){
		sf::FloatRect currRect = tempPlatList.front();
		if (currRect.top <= topLeftPos.y){
			if(currRect.left <= topLeftPos.x + dimentions.x && (currRect.left + currRect.width) >= topLeftPos.x){
				if(currRect.top + currRect.height > closestPlatformY){
					closestPlatformY = currRect.top + currRect.height;
				}
			}
		}
		tempPlatList.pop_front();
	}

	return closestPlatformY;
}

float LevelManager::getWallLeft(sf::Vector2f topLeftPos, sf::Vector2f dimentions){
	//convert to a grid position
	float closestPlatformX = 0;
	std::list<sf::FloatRect> tempPlatList = *platformList;//list of platforms to pop
	for(int i = 0; i < platformList->size(); i++){
		sf::FloatRect currRect = tempPlatList.front();
		if ((currRect.left + currRect.width) <= topLeftPos.x){
			if(currRect.top < (topLeftPos.y + dimentions.y) && (currRect.top + currRect.height) > topLeftPos.y){
				if((currRect.left + currRect.width) > closestPlatformX){
					closestPlatformX = currRect.left + currRect.width;
				}
			}
		}
		tempPlatList.pop_front();
	}
	return closestPlatformX;
}

float LevelManager::getWallRight(sf::Vector2f topLeftPos, sf::Vector2f dimentions){
	//convert to a grid position
	float closestPlatformX = SCREEN_CELL_SIZE.x * 10;//full screen size
	std::list<sf::FloatRect> tempPlatList = *platformList;//list of platforms to pop
	for(int i = 0; i < platformList->size(); i++){
		sf::FloatRect currRect = tempPlatList.front();
		if (currRect.left >= (topLeftPos.x + dimentions.x) ){
			if(currRect.top < (topLeftPos.y + dimentions.y) && (currRect.top + currRect.height) > topLeftPos.y){
				if(currRect.left < closestPlatformX){
					closestPlatformX = currRect.left;
				}
			}
		}
		tempPlatList.pop_front();
	}
	return closestPlatformX;
}

void LevelManager::populateMap(){

	std::map<int, char> xMap;

	for (int i = 0; i < 10; i++){
		if (i == 0){xMap[0] = 'x'; xMap[1] = 'x'; xMap[2] = 'x'; xMap[3] = 'x'; xMap[4] = 'x'; xMap[5] = 'x'; xMap[6] = 'x'; xMap[7] = 'x'; xMap[8] = 'x'; xMap[9] = 'x';}
		else if (i == 1){xMap[0] = 'x'; xMap[1] = 'x'; xMap[2] = 'x'; xMap[3] = 'x'; xMap[4] = 'x'; xMap[5] = 'x'; xMap[6] = 'x'; xMap[7] = 'x'; xMap[8] = 'x'; xMap[9] = 'x';}
		else if (i == 2){xMap[0] = 'x'; xMap[1] = 'x'; xMap[2] = 'x'; xMap[3] = 'x'; xMap[4] = 'x'; xMap[5] = 'x'; xMap[6] = 'x'; xMap[7] = 'p'; xMap[8] = 'x'; xMap[9] = 'x';}
		else if (i == 3){xMap[0] = 'x'; xMap[1] = 'x'; xMap[2] = 'x'; xMap[3] = 'x'; xMap[4] = 'x'; xMap[5] = 'x'; xMap[6] = 'x'; xMap[7] = 'p'; xMap[8] = 'x'; xMap[9] = 'x';}
		else if (i == 4){xMap[0] = 'x'; xMap[1] = 'x'; xMap[2] = 'x'; xMap[3] = 's'; xMap[4] = 'x'; xMap[5] = 'x'; xMap[6] = 'x'; xMap[7] = 'p'; xMap[8] = 'x'; xMap[9] = 'x';}
		else if (i == 5){xMap[0] = 'p'; xMap[1] = 'x'; xMap[2] = 'p'; xMap[3] = 'p'; xMap[4] = 'p'; xMap[5] = 'p'; xMap[6] = 'x'; xMap[7] = 'x'; xMap[8] = 'x'; xMap[9] = 'x';}
		else if (i == 6){xMap[0] = 'p'; xMap[1] = 'x'; xMap[2] = 'x'; xMap[3] = 'x'; xMap[4] = 'x'; xMap[5] = 'x'; xMap[6] = 'x'; xMap[7] = 'x'; xMap[8] = 'x'; xMap[9] = 'p';}
		else if (i == 7){xMap[0] = 'p'; xMap[1] = 'p'; xMap[2] = 'x'; xMap[3] = 'x'; xMap[4] = 'x'; xMap[5] = 'x'; xMap[6] = 'p'; xMap[7] = 'p'; xMap[8] = 'x'; xMap[9] = 'p';}
		else if (i == 8){xMap[0] = 'p'; xMap[1] = 'p'; xMap[2] = 'p'; xMap[3] = 'x'; xMap[4] = 'x'; xMap[5] = 'x'; xMap[6] = 'x'; xMap[7] = 'x'; xMap[8] = 'x'; xMap[9] = 'p';}
		else if (i == 9){xMap[0] = 'p'; xMap[1] = 'p'; xMap[2] = 'p'; xMap[3] = 'p'; xMap[4] = 'x'; xMap[5] = 'x'; xMap[6] = 'x'; xMap[7] = 'x'; xMap[8] = 'x'; xMap[9] = 'p';}

		gridMap[i] = xMap;
	}
}

void LevelManager::buildTiledLevel(int p_room, bool* isDone){
	//Read from a text file
	//Each character represents a cell
	//the final line represents the background image
	*isDone = false;
	buildTiledLevel(p_room);
	*isDone = true;
}

void LevelManager::buildTiledLevel(int p_room){
	//Read from a text file
	//Each character represents a cell
	//the final line represents the background image
	clearLevel();

	if(m_LevelSet == 0){
		if(p_room == 1){
			//m_mapLoader.TMXToMap("media/Maps/testTiles.tmx");
			m_mapLoader.TMXToMap("media/Maps/L0S0.tmx");
		}
		else if(p_room == 2){
			m_mapLoader.TMXToMap("media/Maps/L0S1.tmx");
		}
	}
	else if(m_LevelSet == 1){
		if(p_room == 1){
			m_mapLoader.TMXToMap("media/Maps/L1S0.tmx");
		}
		else if(p_room == 2){
			m_mapLoader.TMXToMap("media/Maps/L1S1.tmx");
		}
	}
	else if(m_LevelSet == 2){
		if(p_room == 1){
			m_mapLoader.TMXToMap("media/Maps/L2S0.tmx");
		}
		else if(p_room == 2){
			m_mapLoader.TMXToMap("media/Maps/L2S1.tmx");
		}
	}
	else if(m_LevelSet == 3){
		if(p_room == 1){
			m_mapLoader.TMXToMap("media/Maps/L3S0.tmx");
		}
		else if(p_room == 2){
			m_mapLoader.TMXToMap("media/Maps/L3S1.tmx");
		}
	}

	for(int l = 0; l < m_mapLoader.getNumOfLayers(); l++)
	{//current layer	
		for(int y = 0; y < m_mapLoader.getMapHeight() ; y++)	
		{	
			for(int x = 0; x < m_mapLoader.getMapWidth(); x++)	
			{	
				int tileValue = m_mapLoader.getCurrentMapTile(l,x,y);
				if(tileValue != 0)
				{
					addTile(x,y,l,tileValue);
				}
			}
		}
	}
	m_currentRoom = p_room;
}

bool LevelManager::loadMedia(){
	bool retBool = true;
	if(!m_levelTexture.loadFromFile("media/Spritesheets/backgroundSS1-320.png")){
		retBool = false;
	}
	SSImageSize = sf::Vector2i(m_levelTexture.getSize().x / FRAMES_PER_ROW, m_levelTexture.getSize().y / SPRITE_SHEET_ROWS);
	m_levelTexture.setSmooth(false);
	m_levelTextureSprite.setTexture(m_levelTexture);
	return retBool;
}

void LevelManager::addTile(int gridx, int gridy, int layer, int tileValue){
	if(tileValue!=0){
		addPlatform(gridx, gridy, 1);
	}
	int SSgridX = tileValue;
	int SSgridY = 0;

	while(SSgridX > FRAMES_PER_ROW){
		SSgridY ++;
		SSgridX -= FRAMES_PER_ROW;
	}

	m_levelTextureSprite = sf::Sprite();
	sf::FloatRect currRec = getDrawRect(gridx,gridy);
	sf::RectangleShape tempShape;
	tempShape.setSize(sf::Vector2f(currRec.width, currRec.height));
	tempShape.setPosition(currRec.left, currRec.top);

	m_levelTextureSprite.setScale(SCREEN_CELL_SIZE.x / SSImageSize.x ,SCREEN_CELL_SIZE.y / SSImageSize.y );
	m_levelTextureSprite.setPosition(sf::Vector2f(gridx * SCREEN_CELL_SIZE.x ,gridy * SCREEN_CELL_SIZE.y));
	m_levelTextureSprite.setTexture(m_levelTexture);
	m_levelTextureSprite.setTextureRect(sf::IntRect(SSgridX * SSImageSize.x, SSgridY * SSImageSize.y, SSImageSize.x, SSImageSize.y));
	tileSpritesList.push_back(m_levelTextureSprite);
}

void LevelManager::drawAllTiles(sf::RenderWindow* window){
	list<sf::Sprite> tempSpriteList = tileSpritesList;

	while (tempSpriteList.size() > 0)
	{
		window->draw(tempSpriteList.front());
		tempSpriteList.pop_front();
	}
}

void LevelManager::clearLevel(){
	wallList->clear();
	platformList->clear();
	envirementItemList->clear();
	itemList->clear();
	tileSpritesList.clear();
}

void LevelManager::setLevelSet(int levelSet){
	m_LevelSet = levelSet;
}

int LevelManager::getLevelSet(){
	return m_LevelSet;
}

int LevelManager::getCurrentRoom()
{
	return m_currentRoom;
}