#pragma once
#include <thread>
#include <mutex>
#include "Loader.h"

using namespace std;

class LoadingScreen
{
//this class controles the screen's visuals while a sepreate thread loads the entities in the loader class
public:
	static LoadingScreen* getInstance();
	void run(sf::RenderWindow* windowRef);

private:
	LoadingScreen();
	static LoadingScreen* m_instance;
};