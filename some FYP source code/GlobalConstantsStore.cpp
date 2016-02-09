#include "stdafx.h"
#include "GlobalConstantsStore.h"

GlobalConstantsStore* GlobalConstantsStore::m_instance;

GlobalConstantsStore* GlobalConstantsStore::getInsatnce()
{
	if(m_instance == 0)
	{
		m_instance = new GlobalConstantsStore();
	}
	return m_instance;
}

void GlobalConstantsStore::init(sf::Vector2f p_screenDimensions)
{
	SCREEN_DIMENSIONS = p_screenDimensions;
}
	
sf::Vector2f GlobalConstantsStore::getScreenDimensions()
{
	return SCREEN_DIMENSIONS;
}

GlobalConstantsStore::GlobalConstantsStore(void)
{
}

GlobalConstantsStore::~GlobalConstantsStore(void)
{
}
