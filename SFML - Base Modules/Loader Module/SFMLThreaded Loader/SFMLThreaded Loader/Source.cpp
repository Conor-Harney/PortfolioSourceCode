#include "LoadingScreen.h"
#include "Loader.h"
#include "testEnv.h"
#include "MediaPack.h"
#include <thread>
#include <iostream>
#include <sstream>
#include <math.h>
#include <limits>

#include <direct.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stack>   

//#include "stdafx.h" 
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 
 
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <iostream> 
#define _USE_MATH_DEFINES
#include <math.h>
#include "SFML\Audio.hpp"

double m_precentLoaded = 0;
sf::RenderWindow * windowRef;

int main()
{	
	MediaPack mp1 = MediaPack("mp1");
	mp1.getMusic("test")->openFromFile("Media/testPack2/Music/uneasy.ogg");

	mp1.getMusic("test")->play();

	// Create the main window 
    sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Multi-threaded SFML loader"); 
    windowRef = &window;
    // Start game loop 
	//Loader::getInstance()->runLoad(&window);
	Loader::getInstance()->createMediaPack("testPack2");
	//cout << Loader::getInstance()->countDir("test");
	//Loader::getInstance()->runLoad(&window);
	//Loader::getInstance()->runLoad(&window);
    while (window.isOpen()) 
    { 
        // Process events 
        sf::Event Event; 
        while (window.pollEvent(Event)) 
        { 
            // Close window : exit 
            if (Event.type == sf::Event::Closed) 
                window.close(); 
   
            // Escape key : exit 
            if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape)) 
                window.close(); 

        } 
         
		//prepare frame
        window.clear();
        window.display(); 
    } //loop back for next frame
   
	system("pause");
    return EXIT_SUCCESS; 
}

void test(sf::SoundBuffer sb)
{
	sf::SoundBuffer mysb = sb;
}