#ifndef LAYER_H
#define LAYER_H

#include <string>
#include <map>

using namespace std;

class Layer
{
public:
	Layer();
	~Layer();
	void AddTile(string, int);
	map<string, int> GetTiles();
private:
	map<string, int> m_tiles;
};
#endif