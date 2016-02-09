#pragma once
#include <list>
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 

using namespace std;

class Controller
{
public:
	static Controller* getInstance();
	enum ActionType{
		Left,	/*left or A key*/
		Right,	/*right or D key*/
		Up,		/*up or W key*/
		Down,	/*Down or D key*/
		Sprint, /*Shift*/
		Jump,	/*Space key*/
		Action,	/*Enter*/
		MenuSelect,	/*select a menu or inventory option*/
		MenuReturn,	/*return - inventory or menu*/
		ToggleInventory,	/*Tab key*/
		ToggleMenu, /*turn the menu on/off*/
		LevelLeft, /*change the level state left*/
		LevelRight,
		LevelToggle,
		ZoomOut
	};
	enum GamePadInput{
		A,
		B,
		X,
		Y,
		LEFT_BUMPER,
		RIGHT_BUMPER,
		LEFT_TRIGGER,
		RIGHT_TRIGGER,
		LEFT_STICK,
		RIGHT_STICK,
		D_PAD_UP,
		D_PAD_DOWN,
		D_PAD_LEFT,
		D_PAD_RIGHT,
		LEFT_STICK_LEFT,
		LEFT_STICK_RIGHT,
		LEFT_STICK_UP,
		LEFT_STICK_DOWN,
		RIGHT_STICK_LEFT,
		RIGHT_STICK_RIGHT,
		RIGHT_STICK_UP,
		RIGHT_STICK_DOWN,
		START,
		SELECT
	};

	list<ActionType> getKeyList();
	list<ActionType> getControllerList();

	bool dirrectionKeyPushed();
	bool actionLeft();
	bool actionRight();
	bool actionUp();
	bool actionDown();
	bool actionSprint();
	bool actionJump();
	bool actionAction();
	bool actionInventory();
	bool actionMenu();
	bool actionMenuSelect();
	bool actionMenuReturn();
	bool actionLeftOnce();//doesn't return for held keys
	bool actionRightOnce();//doesn't return for held keys
	bool actionUpOnce();
	bool actionDownOnce();
	bool actionLevelLeft();
	bool actionLevelRight();
	bool actionToggleLevel();
	bool actionZoomOut();

	list<GamePadInput> getControllerInput();
	bool keyPressedOnce(sf::Keyboard::Key key);
	
private:
	Controller(void);
	~Controller(void);
	static Controller* m_instance;
	map<GamePadInput, unsigned int> controllerMap;
	bool checkGamepadButtonDown(string button);
	map<Controller::ActionType,bool> actionHeld;
	map<sf::Keyboard::Key ,bool> keyHeld;
	
};

