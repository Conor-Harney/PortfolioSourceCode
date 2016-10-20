#pragma once
#include <thread>
#include <mutex>
#include "SFML/Graphics.hpp" 
#include "LoadingScreen.h"
#include <memory.h>
#include <list>
#include <Map>
#include <queue>
#include "dirent.h"
#include <sys/types.h>
#include <sys/stat.h>

#include <thread>
#include <iostream>
#include <sstream>
#include <math.h>
#include <limits>

#include <direct.h>
#include <sys/types.h>
#include <sys/stat.h> 

using namespace std;
class Loader
{
//this class will load all call the loading screen and then load all the entities 
public:
	static Loader* getInstance();
	bool getLoaded();
	void runLoad(sf::RenderWindow* windowRef);
	float getPercentLoaded();
	~Loader();
	

	void createMediaPack(string packName);//create a named folder and its subfolders inside the media directory
	void loadPack(string packName);//load a named pack in the media folder into memory.
	void unloadPack();//remove the media acociated with a pack from memory.
	int countFilesInPack(string packName);//count the files inside the m_mediaFolders in a pack

private:
	Loader();
	static Loader* m_instance;
	float m_percentLoaded;
	void loadAll();
	void callLoadingScreen(sf::RenderWindow* windoeRef);
	
	void setMediaFolders();//create a list of the folders to be created and counted inside media packs.

	const string m_mediaDirectory;
	std::vector<string> m_mediaFolders;//a vector of folders to be created inside media folder packs.
	int countFilesInFolder(string directory);//count the files in a spicific folder
	vector<string> getFileNamesInFolder(string folderDirectory);//get the names of all the files in a folder 
	
};

