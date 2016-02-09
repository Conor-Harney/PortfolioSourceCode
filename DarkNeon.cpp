//////////////////////////////////////////////////////////// 
// Headers 
//////////////////////////////////////////////////////////// 
#include "stdafx.h" 
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
#include "Game.h"
//#include "httpCaller.h"
//#include "ScoreBoard.h"

int main() 
{ 
	//fill the scoreboard with fake values
	//httpCaller tempCaller;
	/*PlayerInformationSet* m_playIS = new PlayerInformationSet(0,"the",15);
	tempCaller.postToScoreBoard(m_playIS);
	m_playIS = new PlayerInformationSet(0,"quick",80);
	tempCaller.postToScoreBoard(m_playIS);
	m_playIS = new PlayerInformationSet(0,"brown",65);
	tempCaller.postToScoreBoard(m_playIS);
	m_playIS = new PlayerInformationSet(0,"fox",23);
	tempCaller.postToScoreBoard(m_playIS);
	m_playIS = new PlayerInformationSet(0,"jumps",94);
	tempCaller.postToScoreBoard(m_playIS);
	m_playIS = new PlayerInformationSet(0,"over",11);
	tempCaller.postToScoreBoard(m_playIS);
	m_playIS = new PlayerInformationSet(0,"the",87);
	tempCaller.postToScoreBoard(m_playIS);
	m_playIS = new PlayerInformationSet(0,"lazy",104);
	tempCaller.postToScoreBoard(m_playIS);
	m_playIS = new PlayerInformationSet(0,"dog",3);
	tempCaller.postToScoreBoard(m_playIS);*/
	//vector<PlayerInformationSet> retVect = 
	//sb.setMyScore(PlayerInformationSet(0,"Vick", 50));
	
	const sf::Vector2f* SCREEN_DIMENTIONS = new const sf::Vector2f(800, 600);

	// Create the main window 
	sf::RenderWindow window(sf::VideoMode(SCREEN_DIMENTIONS->x, SCREEN_DIMENTIONS->y, 32), "Dark Neon");
	

	sf::RenderWindow * windowRef = &window;
	sf::Time timeElasped;
	sf::Clock clock;
	window.setMouseCursorVisible(false);
	ResourceManager::getInstance()->init(&window);
	bool* restartGame = new bool(false);
	Game* game = new Game(SCREEN_DIMENTIONS, restartGame);
	// Start Game loop 
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
			//if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape)) 
			//    window.close(); 


		} 

		//prepare frame
		//window.clear();
		window.clear(sf::Color::White);

		//lag tester
		//for(double i = 0; i < 59999999; i += 1){}

		timeElasped = clock.restart();
		//cout << timeElasped.asSeconds() << endl;
		game->update(timeElasped);
		game->draw(windowRef);


		// Finally, display rendered frame on screen 
		window.display(); 
		if(*restartGame == true)
		{
			//game->~Game();
			//game = new Game(SCREEN_DIMENTIONS,restartGame);
			*restartGame = false;
		}
	} //loop back for next frame

	return EXIT_SUCCESS; 
}

//INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
//   PSTR lpCmdLine, INT nCmdShow)
//{
//   return 0;
//}