#pragma once
#include <map>
#include <list>
#include <SFML\Window\Joystick.hpp>
#include <SFML\Window\Keyboard.hpp>
#include <SFML\Window\Event.hpp>
#include <locale>
#include <algorithm>

//this class will only handle raw input
//It will only translate to the level of a button or input method name - ie: [ Game Pad - XBox Controller - Port 1 - 'A' button ]
//Translation to an action will be handled by an input interpretation class or the players token itself.

/*
	NOTE:
	PRESSED:	BUTTON IS DOWN THIS CHECK, WAS NOT DOWN LAST CHECK
	DOWN:		BUTTON IS DOWN THIS CHECK, MAY OR MAY NOT HAVE ALSO BEEN DOWN LAST CHECK
*/
namespace GamePadButton
{
	enum GamePadButton
	{//possible types of gamepad presses
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
}


class InputManager
{
public:
	static InputManager* getInstance();//return the static instanc of this singilton class

	//gamepad
	bool buttonPressed(GamePadButton::GamePadButton button, unsigned int controllerNum);
	bool buttonDown(GamePadButton::GamePadButton button, unsigned int controllerNum);
	
	//keyboard
	bool buttonPressed(sf::Keyboard::Key button);
	bool buttonDown(sf::Keyboard::Key button);
	void getInputString(std::string* stringToEdit);//return a string of the characters pressed on the keyboard
	void setEvent(sf::Event* eventPtr);
	void setUnsafeCharacterBlocker(bool onOff);

private:
	InputManager(void);
	~InputManager(void);
	static InputManager* m_instance;
	
	//keyboard vars
	std::list<sf::Keyboard::Key> m_heldKeys;
	std::map<sf::Keyboard::Key, std::string> m_textKeysMap;
	std::list<sf::Keyboard::Key> m_keyList;
	void setUpKeyboard();
	sf::Event* m_event;
	char m_lastKeyPressed;
	bool m_blockUnsafeCharacters;//disallow unsafe characters specified in the m_unsafeCharactersList
	std::list<char> m_unsafeCharactersList;
	void checkEventInput(std::string* stringToEdit);
	void checkEventlessInput(std::string* stringToEdit);
	//gamepad vars
	std::map<GamePadButton::GamePadButton, unsigned int> m_controllerMap;//The number value assigned to each XBox controller button
	std::list<GamePadButton::GamePadButton> m_heldGamePadButtons;
	void setUpXBoxController();
};

