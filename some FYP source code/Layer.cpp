#include "stdafx.h"
#include "Layer.h"

Layer::Layer()
{
}

Layer::~Layer()
{
}

map<string, int> Layer::GetTiles()
{
	return m_tiles;
}

void Layer::AddTile(string key, int value)
{
	m_tiles.insert(pair<string, int>(key, value));
}