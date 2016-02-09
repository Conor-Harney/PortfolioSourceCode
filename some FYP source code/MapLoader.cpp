#include "stdafx.h"
#include "MapLoader.h"

MapLoader::MapLoader()
{
	m_p_map = new Map();
}

MapLoader::~MapLoader()
{
	delete(m_p_map);
}

int MapLoader::Transpose(int& v)
{
	if (v != 0x00)
	{
		return v - 0x01;
	}
	else
	{
		return v;
	}
}

string MapLoader::KeyGenerator(const int& x, const int& y)
{
	std::ostringstream oss;
	oss << x << "," << y;
	string key = oss.str();
	return key;
}


Map MapLoader::TMXToMap(const char* filePath){
	Map tempMap = Map();
	bool loop = true;
	Layer* tileLayer = NULL;
	int gid;
	layerKeys.clear();
	XMLDocument m_doc;

	if (m_doc.LoadFile(filePath) == 0)
	{
		//DEBUG_MSG("Fetching Map Information");
		XMLElement* element = m_doc.FirstChildElement("map");
		//DEBUG_MSG(element->GetText());

		if (element != NULL)
		{
			tempMap.SetWidth(atoi(element->Attribute("width")));
			tempMap.SetHeight(atoi(element->Attribute("height")));
			int tilesOnMap = tempMap.GetWidth() * tempMap.GetHeight();

			//m_doc.
			XMLElement* layers = m_doc.FirstChildElement("map")->FirstChildElement("layer");
			Layer tempLayre;
			int layerCounter = 0;
			while (loop)
			{
				string layerName = layers->Attribute("name");
				layerKeys[layerCounter] = layerName;
				layerCounter++;
				tileLayer = new Layer();

				XMLElement* tile = layers->FirstChildElement("data")->FirstChild()->ToElement();

				if (tile != NULL)
				{
					gid = atoi(tile->Attribute("gid"));

					for (int y = 0; y < tempMap.GetHeight(); y++)
					{
						for (int x = 0; x < tempMap.GetWidth(); x++)
						{
							gid = Transpose(gid); //Transpose map values

							tileLayer->AddTile(KeyGenerator(x, y), gid);

							tile = tile->NextSiblingElement();
							if (tile != NULL)
							{
								gid = atoi(tile->Attribute("gid"));
							}
						}
					}

					tempMap.AddLayer(layerName, tileLayer);//Add finished layer to Map

				}

				layers = layers->NextSiblingElement();

				if (layers == NULL)
				{
					loop = false;
				}
			}//End: While gids
		}//End: File loaded
	}
	m_p_map = new Map(tempMap);
	return tempMap;
}

int MapLoader::getTile(Map fromMap, string layerName, int x, int y){
	string index = KeyGenerator(x,y);
	int tileValue = fromMap.GetLayers()[layerName]->GetTiles()[index];
	return tileValue;
}

int MapLoader::getTile(Map* fromMap, string layerName, int x, int y){
	string index = KeyGenerator(x,y);
	int tileValue = fromMap->GetLayers()[layerName]->GetTiles()[index];
	return tileValue;
}

int MapLoader::getCurrentMapTile(string layerName, int x, int y){
	string index = KeyGenerator(x,y);
	int tileValue = m_p_map->GetLayers()[layerName]->GetTiles()[index];
	return tileValue;
}

int MapLoader::getCurrentMapTile(int layerNum, int x, int y){
	string index = KeyGenerator(x,y);
	int tileValue = m_p_map->GetLayers()[layerKeys[layerNum]]->GetTiles()[index];
	return tileValue;
}

Map* MapLoader::getMap(){
	return m_p_map;
}

int MapLoader::getMapHeight(){
	return m_p_map->GetHeight();
}

int MapLoader::getMapWidth(){
	return m_p_map->GetWidth();
}

int MapLoader::getNumOfLayers(){
	return m_p_map->getNumOfLayers();
}
