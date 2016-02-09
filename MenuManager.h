#pragma once
#include "EnumStore.h"
#include "ResourceManager.h"
#include "GlobalConstantsStore.h"
#include "Controller.h"
#include "AudioManager.h"
#include "EnterNameScreen.h"
class MenuManager
{
public:
	static MenuManager* getInstance();
	void render();
	void updateState(EnumStore::GAME_STATE p_gameState);
	void nextButtonDown();
	void nextButtonUp();
	void inMenuUpdate();
	enum menuOptions
	{
		NewGame,
		ScoreBoard,
		Continue,
		Mute,
		Tutorial,
		AcceptName,
		None
	};
	menuOptions getOptionCall();
	

private:
	static MenuManager* m_instance;
	MenuManager(void);
	~MenuManager(void);
	EnumStore::GAME_STATE m_currentGameState;
	sf::Sprite* m_menuBackground;
	sf::Sprite* m_newGameButton;
	sf::Sprite* m_continueButton;
	sf::Sprite* m_muteButton;
	sf::Sprite* m_tutorialButton;
	sf::Sprite* m_scoreboardButton;
	sf::Sprite* m_buttonHighlighte;
	sf::Sprite* m_tutorialScreen;
	sf::Vector2f m_buttonSize;
	float buttonYPoss[4];
	float buttonXPos;
	int buttonsInCurrentMenu;
	int m_currentButton;
	bool m_optionSellected;
	
};

