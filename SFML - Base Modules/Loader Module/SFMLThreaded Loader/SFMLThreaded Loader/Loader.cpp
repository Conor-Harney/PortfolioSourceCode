#include "Loader.h"

Loader* Loader::m_instance = 0;
//std::mutex ldrMu;

Loader* Loader::getInstance()
{
	//std::lock_guard<std::mutex> guard(ldrMu);
	if(m_instance == 0)
	{
		m_instance = new Loader();	
	}
	return m_instance;
}

Loader::Loader(void): m_mediaDirectory("./Media")
{
	setMediaFolders();
}

void Loader::runLoad(sf::RenderWindow* windowRef)
{
	windowRef->setActive(false);
	m_percentLoaded = 0;
	std::thread t1(&Loader::loadAll, this);
	std::thread t2(&Loader::callLoadingScreen, this, windowRef);
	t1.join();
	t2.join();
	windowRef->setActive(true);
}

void Loader::callLoadingScreen(sf::RenderWindow* windoeRef)
{
	LoadingScreen::getInstance()->run(windoeRef);
}

Loader::~Loader(void)
{
}

float Loader::getPercentLoaded()
{
	return m_percentLoaded;
}

void Loader::loadAll()
{
	int filesLoaded = 0;
	int filesToLoad = 50;
	string fileName = "Untitled";
	std::string pathStr = "Media/Images/" + fileName + ".png";
	const char* pathChar = pathStr.c_str();
	std::map<string,sf::Texture*> imagesMap;
	for(filesLoaded = 0; filesLoaded < filesToLoad; filesLoaded++)
	{
		string imageName = fileName + std::to_string(filesLoaded);
		imagesMap[imageName] = new sf::Texture();
		if(!imagesMap[imageName]->loadFromFile(pathChar))
		{
			throw;
		}
		m_percentLoaded = ( (filesLoaded + 1.0) / filesToLoad) * 100;
	}
	imagesMap.clear();
}

bool Loader::getLoaded()
{
	if(m_percentLoaded!=100)
	{
		return false;
	}
	else
	{
		return true;
	}
}

int Loader::countFilesInFolder(string directory)
{//count how many files are in the directory

	//SFML can load the following image file formats: bmp, dds, jpg, png, tga, psd
	//But keep in mind that not all variants of each format are supported.
	//The Audio module is capable of playing wav, ogg/vorbis and flac files.

	DIR *dir;
	struct dirent *ent;
	int counter = 0;
	if ((dir = opendir (directory.c_str())) != NULL) 
	{
		
		/* print all the files and directories within directory */
		for(int i = 0; (ent = readdir (dir)) != NULL; i++)
		{
			if(i > 1)
			{//the first two returns are "." and ".."... I don't know why. so skip 'em.
				counter++;
			}
		}
		closedir (dir);
	} 
	else 
	{
		/* could not open directory */
		perror ("");
		counter = -1;
	}
	return counter;
}

void Loader::createMediaPack(string packName)
	//create a named folder and its subfolders inside the media directory
	//first create the m_mediaDirectory (usually ./Media folder)
	//next create the packName folder inside the m_mediaDirectory folder
	//next create the subfolders named in m_mediaFolders inside the packName folder
	//only create the folders if they have not already been created
{
	struct stat info;
	std::queue<string> pathnames;
	string baseDir = m_mediaDirectory + "/" + packName;
	vector<string>::iterator iter = m_mediaFolders.begin();

	//fill the pathnames with directories
	pathnames.push(m_mediaDirectory);
	pathnames.push(baseDir);
	baseDir += "/";
	for(int i = 0; i < m_mediaFolders.size(); i++)
	{
		pathnames.push(baseDir + *iter);
		iter++;
	}
	
	while(pathnames.size())
	{

		if( stat( pathnames.front().c_str(), &info ) != 0 )
		{//folder may not exist
			mkdir(pathnames.front().c_str());//cannot access
			printf( "%s created\n", pathnames.front().c_str() );
		}
		else if( info.st_mode & S_IFDIR )  // S_ISDIR() doesn't exist on my windows 
		{//folder exists
			//printf( "%s is a directory\n", pathnames.top() );
		}
		else
		{//safty catch
			mkdir(pathnames.front().c_str());
			printf( "%s created\n", pathnames.front().c_str() );
		}
		pathnames.pop();
	}
}

void Loader::loadPack(string packName)//load a named pack in the media folder into memory.
{

}

void Loader::unloadPack()//remove the media acociated with a pack from memory.
{

}

void Loader::setMediaFolders()//create a list of the folders to be created and counted inside media packs.
{
	m_mediaFolders.push_back("Sound Effects");
	m_mediaFolders.push_back("Music");
	m_mediaFolders.push_back("Images");
	m_mediaFolders.push_back("Spritesheets");
}

int Loader::countFilesInPack(string packName)
	//count the files inside the m_mediaFolders in a pack
{
	int count = 0;
	string packDir = m_mediaDirectory + "/" + packName + "/";
	vector<string>::iterator iter = m_mediaFolders.begin();
	for(int i = 0; i < m_mediaFolders.size(); i++)
	{
		if(countFilesInFolder(packDir + *iter) != -1)
		{
			count += countFilesInFolder(packDir + *iter);
		}
		iter++;
	}
	return count;
}

vector<string> Loader::getFileNamesInFolder(string folderDirectory)//get the names of all the files in a folder
{
	vector<string> fileNames;
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir (folderDirectory.c_str())) != NULL) 
	{
		
		/* print all the files and directories within directory */
		for(int i = 0; (ent = readdir (dir)) != NULL; i++)
		{
			if(i > 1)
			{//the first two returns are "." and ".."... I don't know why. so skip 'em.
				fileNames.push_back(ent->d_name);
			}
		}
		closedir (dir);
	} 
	else 
	{
		/* could not open directory */
		perror ("");
	}
	return fileNames;
}