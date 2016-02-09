#include "stdafx.h"
#include "Map.h"

void Map::SetWidth(int width)
{
	m_width = width;
}

int Map::GetWidth()
{
	return m_width;
}

void Map::SetHeight(int height)
{
	m_height = height;
}

int Map::GetHeight()
{
	return m_height;
}

void Map::AddLayer(string key, Layer* layer)
{
	m_layers.insert(pair<string, Layer*>(key, layer));
}

map<string, Layer*> Map::GetLayers()
{
	return m_layers;
}

int Map::countInLayer(string& key)
{
	return m_layers.count(key);
}

int Map::getNumOfLayers(){
	return m_layers.size();
}