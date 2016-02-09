#pragma once
#include "TinyXML2.h"
#include <iomanip>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <string>
#include "Layer.h"
#include "Map.h"


using namespace std;
using namespace tinyxml2;

class MapLoader
{
public:

	MapLoader();
	~MapLoader();
	
	
	//Sets Map Data
	void SetData(map<string, string>&);
	//Generate Map Keys
	string KeyGenerator(const int& x, const int&y);
	//Check if file Exists
	static bool FileExist(const string&);
	//Find and replace text in files (Start and End Tags)
	bool FindAndReplaceText(const string&);
	
	//Preprocessor to add XML escape characters to file line output
	string Escape(const string&);
	Map TMXToMap(const char* filePath);
	int getTile(Map  fromMap, string layerName, int x, int y);
	int getTile(Map* fromMap, string layerName, int x, int y);
	int getCurrentMapTile(string layerName, int x, int y);
	int getCurrentMapTile(int layerNum, int x, int y);
	Map* getMap();
	int getMapHeight();
	int getMapWidth();
	int getNumOfLayers();
private:
	Map* m_p_map;
	//XMLDocument m_doc;
	map<std::string, std::string> m_data;
	int Transpose(int&);
	map<int, std::string> layerKeys;
};