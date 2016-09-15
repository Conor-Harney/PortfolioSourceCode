#include "stdafx.h"
#include "InputManager.h"

InputManager* InputManager::m_instance;

InputManager::InputManager(void)
{
	m_event = 0;
	m_lastKeyPressed = '¶';
	setUpXBoxController();
	m_blockUnsafeCharacters = true;
	m_unsafeCharactersList.push_back('<');
	m_unsafeCharactersList.push_back('>');
	m_unsafeCharactersList.push_back('"');
	m_unsafeCharactersList.push_back('\\');
	m_unsafeCharactersList.push_back('\'');
	m_unsafeCharactersList.push_back('/');
	setUpKeyboard();
}


InputManager::~InputManager(void)
{
}

void InputManager::setEvent(sf::Event* eventPtr)
{
	if(m_event == 0)
	{
		m_event = eventPtr;
	}
}

InputManager* InputManager::getInstance()
{
	if(m_instance == 0)
	{
		m_instance = new InputManager();
	}
	return m_instance;
}

void InputManager::setUpXBoxController()
{
	//setup the controller map
	m_controllerMap[GamePadButton::GamePadButton::A]			= 0;
	m_controllerMap[GamePadButton::GamePadButton::B]			= 1;
	m_controllerMap[GamePadButton::GamePadButton::X]			= 2;
	m_controllerMap[GamePadButton::GamePadButton::Y]			= 3;
	m_controllerMap[GamePadButton::GamePadButton::LEFT_BUMPER]	= 4;
	m_controllerMap[GamePadButton::GamePadButton::RIGHT_BUMPER]	= 5;
	m_controllerMap[GamePadButton::GamePadButton::SELECT]		= 6;
	m_controllerMap[GamePadButton::GamePadButton::START]		= 7;
	m_controllerMap[GamePadButton::GamePadButton::LEFT_STICK]	= 8;
	m_controllerMap[GamePadButton::GamePadButton::RIGHT_STICK]	= 9;

	//LT		sf::Joystick::Axis::Z	> 1
	//RT		sf::Joystick::Axis::Z	< 1

	//DP_up		sf::Joystick::PovX		=  100
	//DP_down	sf::Joystick::PovX		= -100
	//DP_left	sf::Joystick::PovY		= -100
	//DP_right	sf::Joystick::PovY		=  100

	//LSLEFT	sf::Joystick::Axis::X	< -10
	//LSRight	sf::Joystick::Axis::X	>  10
	//LSUP		sf::Joystick::Axis::Y	< -10
	//LSDOWN	sf::Joystick::Axis::Y	>  10

	//RSLEFT	sf::Joystick::Axis::U	< -10
	//RSRight	sf::Joystick::Axis::U	>  10
	//RSUP		sf::Joystick::Axis::R	< -10
	//RSDOWN	sf::Joystick::Axis::R	>  10
}

void InputManager::setUpKeyboard()
{
	m_textKeysMap[sf::Keyboard::Key::A] = "a";
	m_keyList.push_back(sf::Keyboard::Key::A);
	m_textKeysMap[sf::Keyboard::Key::B] = "b";
	m_keyList.push_back(sf::Keyboard::Key::B);
	m_textKeysMap[sf::Keyboard::Key::C] = "c";
	m_keyList.push_back(sf::Keyboard::Key::C);
	m_textKeysMap[sf::Keyboard::Key::D] = "d";
	m_keyList.push_back(sf::Keyboard::Key::D);
	m_textKeysMap[sf::Keyboard::Key::E] = "e";
	m_keyList.push_back(sf::Keyboard::Key::E);
	m_textKeysMap[sf::Keyboard::Key::F] = "f";
	m_keyList.push_back(sf::Keyboard::Key::F);
	m_textKeysMap[sf::Keyboard::Key::G] = "g";
	m_keyList.push_back(sf::Keyboard::Key::G);
	m_textKeysMap[sf::Keyboard::Key::H] = "h";
	m_keyList.push_back(sf::Keyboard::Key::H);
	m_textKeysMap[sf::Keyboard::Key::I] = "i";
	m_keyList.push_back(sf::Keyboard::Key::I);
	m_textKeysMap[sf::Keyboard::Key::J] = "j";
	m_keyList.push_back(sf::Keyboard::Key::J);
	m_textKeysMap[sf::Keyboard::Key::K] = "k";
	m_keyList.push_back(sf::Keyboard::Key::K);
	m_textKeysMap[sf::Keyboard::Key::L] = "l";
	m_keyList.push_back(sf::Keyboard::Key::L);
	m_textKeysMap[sf::Keyboard::Key::M] = "m";
	m_keyList.push_back(sf::Keyboard::Key::M);
	m_textKeysMap[sf::Keyboard::Key::N] = "n";
	m_keyList.push_back(sf::Keyboard::Key::N);
	m_textKeysMap[sf::Keyboard::Key::O] = "o";
	m_keyList.push_back(sf::Keyboard::Key::O);
	m_textKeysMap[sf::Keyboard::Key::P] = "p";
	m_keyList.push_back(sf::Keyboard::Key::P);
	m_textKeysMap[sf::Keyboard::Key::Q] = "q";
	m_keyList.push_back(sf::Keyboard::Key::Q);
	m_textKeysMap[sf::Keyboard::Key::R] = "r";
	m_keyList.push_back(sf::Keyboard::Key::R);
	m_textKeysMap[sf::Keyboard::Key::S] = "s";
	m_keyList.push_back(sf::Keyboard::Key::S);
	m_textKeysMap[sf::Keyboard::Key::T] = "t";
	m_keyList.push_back(sf::Keyboard::Key::T);
	m_textKeysMap[sf::Keyboard::Key::U] = "u";
	m_keyList.push_back(sf::Keyboard::Key::U);
	m_textKeysMap[sf::Keyboard::Key::V] = "v";
	m_keyList.push_back(sf::Keyboard::Key::V);
	m_textKeysMap[sf::Keyboard::Key::W] = "w";
	m_keyList.push_back(sf::Keyboard::Key::W);
	m_textKeysMap[sf::Keyboard::Key::X] = "x";
	m_keyList.push_back(sf::Keyboard::Key::X);
	m_textKeysMap[sf::Keyboard::Key::Y] = "y";
	m_keyList.push_back(sf::Keyboard::Key::Y);
	m_textKeysMap[sf::Keyboard::Key::Z] = "z";
	m_keyList.push_back(sf::Keyboard::Key::Z);
	m_textKeysMap[sf::Keyboard::Key::Space] = " ";
	m_keyList.push_back(sf::Keyboard::Key::Space);
	m_textKeysMap[sf::Keyboard::Key::Dash] = "-";
	m_keyList.push_back(sf::Keyboard::Key::Dash);
	m_textKeysMap[sf::Keyboard::Key::Period] = ".";
	m_keyList.push_back(sf::Keyboard::Key::Period);
}

bool InputManager::buttonPressed(sf::Keyboard::Key button)
{//check if a button is pressed that was not pressed last frame
	bool buttonPressed = false;
	bool buttonHeld = false;
	if(buttonDown(button))
	{//button is currently pressed
		for(std::list<sf::Keyboard::Key>::iterator itter = m_heldKeys.begin(); itter != m_heldKeys.end(); itter++)
		{//check if it was held
			if (*itter == button){
				buttonHeld = true;
			}
		}
		if(!buttonHeld)
		{//button is pressed now and was not pressed last check
			buttonPressed = true;
			m_heldKeys.push_back(button);
		}
	}
	else
	{//button is not currently pressed 
		for(std::list<sf::Keyboard::Key>::iterator itter = m_heldKeys.begin(); itter != m_heldKeys.end(); itter++)
		{//so remove it from the held is it was there
			if (*itter == button)
			{
				m_heldKeys.erase(itter);
				break;//if an element is removed, the end point is changed. Use break or an exception error will occur.
			}
		}
	}
	return buttonPressed;
}

bool InputManager::buttonDown(sf::Keyboard::Key button)
{
	return sf::Keyboard::isKeyPressed(button);
}

void InputManager::getInputString(std::string* stringToEdit)
{

	if(m_event == 0)
	{//use a clunky method
		checkEventlessInput(stringToEdit);
	}
	else
	{//use the sf::event method
		checkEventInput(stringToEdit);
	}
}

void InputManager::checkEventInput(std::string* stringToEdit)
{
	if(m_event->type == sf::Event::TextEntered)
		{
			sf::Uint32 input = m_event->text.unicode;
			if (input < 128)
			{
				bool safe = true;
				char pressedKey = static_cast<char>(input);
				if(m_blockUnsafeCharacters)
				{//check for unsafe characters
					for (std::list<char> charItter = m_unsafeCharactersList; charItter.size() > 0; charItter.pop_back())
					{
						if(charItter.back() == pressedKey)
						{
							safe = false;
							
						}
					}
				}
				if(pressedKey != m_lastKeyPressed && safe)
				{
					m_lastKeyPressed = pressedKey;
					switch(input)
					{
						case 8:
							if(stringToEdit->size() > 0)//just incase
							*stringToEdit = stringToEdit->substr(0, stringToEdit->size()-1);
							break;
						default:
							*stringToEdit += pressedKey;	
							break;
					}
				}
			}
		}
		else
		{
			m_lastKeyPressed = '¶';
		}
}

void InputManager::checkEventlessInput(std::string* stringToEdit)
{
	std::string retString = "";
	for(std::list<sf::Keyboard::Key>::iterator itter = m_keyList.begin(); itter != m_keyList.end(); itter++)
	{
		sf::Keyboard::Key mykey = *itter;
		if(buttonPressed(*itter))
		{
			retString += m_textKeysMap[*itter];
		}
	}
	if(buttonDown(sf::Keyboard::Key::LShift) || buttonDown(sf::Keyboard::Key::RShift))
	{
		transform(retString.begin(), retString.end(), retString.begin(), ::toupper);
	}
	if(buttonPressed(sf::Keyboard::Key::BackSpace))
	{
		if(stringToEdit->size())
		{
			stringToEdit->pop_back();
		}
	}
	stringToEdit->append(retString);
}

bool InputManager::buttonPressed(GamePadButton::GamePadButton button, unsigned int controllerNum)
{//check if a button is pressed that was not pressed last frame
	bool buttonPressed = false;
	bool buttonHeld = false;
	if(buttonDown(button, controllerNum))
	{//button is currently pressed
		for(std::list<GamePadButton::GamePadButton>::iterator itter = m_heldGamePadButtons.begin(); itter != m_heldGamePadButtons.end(); itter++)
		{//check if it was held
			if (*itter == button){
				buttonHeld = true;
			}
		}
		if(!buttonHeld)
		{//button is pressed now and was not pressed last check
			buttonPressed = true;
			m_heldGamePadButtons.push_back(button);
		}
	}
	else
	{//button is not currently pressed 
		for(std::list<GamePadButton::GamePadButton>::iterator itter = m_heldGamePadButtons.begin(); itter != m_heldGamePadButtons.end(); itter++)
		{//so remove it from the held is it was there
			if (*itter == button)
			{
				m_heldGamePadButtons.erase(itter);
				break;//if an element is removed, the end point is changed. Use break or an exception error will occur.
			}
		}
	}
	return buttonPressed;
}

bool InputManager::buttonDown(GamePadButton::GamePadButton button, unsigned int controllerNum)
{
	return sf::Joystick::isButtonPressed(controllerNum, m_controllerMap[button]);
}

void InputManager::setUnsafeCharacterBlocker(bool onOff)
{
	m_blockUnsafeCharacters = onOff;
}