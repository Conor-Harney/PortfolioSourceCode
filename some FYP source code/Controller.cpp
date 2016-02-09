#include "stdafx.h"
#include "Controller.h"

Controller* Controller::m_instance;

Controller* Controller::getInstance()
{
	if(m_instance == 0)
	{
		m_instance = new Controller();
	}
	return m_instance;
}

Controller::Controller(void)
{

	controllerMap[GamePadInput::A]				= 0;
	controllerMap[GamePadInput::B]				= 1;
	controllerMap[GamePadInput::X]				= 2;
	controllerMap[GamePadInput::Y]				= 3;
	controllerMap[GamePadInput::LEFT_BUMPER]	= 4;
	controllerMap[GamePadInput::RIGHT_BUMPER]	= 5;
	controllerMap[GamePadInput::SELECT]			= 6;
	controllerMap[GamePadInput::START]			= 7;
	controllerMap[GamePadInput::LEFT_STICK]		= 8;
	controllerMap[GamePadInput::RIGHT_STICK]	= 9;

	actionHeld[Controller::ActionType::Up]				= false;
	actionHeld[Controller::ActionType::Down]			= false;
	actionHeld[Controller::ActionType::Left]			= false;
	actionHeld[Controller::ActionType::Right]			= false;
	actionHeld[Controller::ActionType::Sprint]			= false;
	actionHeld[Controller::ActionType::Jump]			= false;
	actionHeld[Controller::ActionType::Action]			= false;
	actionHeld[Controller::ActionType::ToggleMenu]		= false;
	actionHeld[Controller::ActionType::ToggleInventory]	= false;
	actionHeld[Controller::ActionType::MenuReturn]		= false;
	actionHeld[Controller::ActionType::MenuSelect]		= false;
	actionHeld[Controller::ActionType::LevelLeft]		= false;
	actionHeld[Controller::ActionType::LevelRight]		= false;
	actionHeld[Controller::ActionType::LevelToggle]		= false;
	actionHeld[Controller::ActionType::ZoomOut]			= false;




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


Controller::~Controller(void)
{
}

list<Controller::ActionType> Controller::getKeyList(){
	list<Controller::ActionType> returnList;

	if (actionLeft())
	{
		returnList.push_back(ActionType::Left);
	}
	else if (actionRight())
	{
		returnList.push_back(ActionType::Right);
	}

	if (actionUp())
	{
		returnList.push_back(ActionType::Up);
	}
	else if (actionDown())
	{
		returnList.push_back(ActionType::Down);
	}

	if(actionSprint()){
		returnList.push_back(ActionType::Sprint);
	}

	if(actionJump()){
		returnList.push_back(ActionType::Jump);
	}

	if(actionAction()){
		returnList.push_back(ActionType::Action);
	}

	return returnList;
}

list<Controller::ActionType> Controller::getControllerList(){
	list<Controller::ActionType> returnList;

	if(sf::Joystick::isConnected(0)){
		if (actionLeft())
		{
			returnList.push_back(ActionType::Left);
		}
		else if (actionRight())
		{
			returnList.push_back(ActionType::Right);
		}

		if (actionUp())
		{
			returnList.push_back(ActionType::Up);
		}
		else if (actionDown())
		{
			returnList.push_back(ActionType::Down);
		}

		if(actionSprint()){
			returnList.push_back(ActionType::Sprint);
		}

		if(actionJump()){
			returnList.push_back(ActionType::Jump);
		}

		if(actionAction()){
			returnList.push_back(ActionType::Action);
		}
	}
	return returnList;
}


bool Controller::actionLeft(){

	bool retBool = false;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)){//direction left
		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)){//direction right not sellected
			retBool = true;
		}
	}
	if(sf::Joystick::isConnected(0)){
		const float STICK_RESISTANCE = 90;
		if(sf::Joystick::getAxisPosition(0,sf::Joystick::Axis::X) < -STICK_RESISTANCE){
			retBool = true;
		}
	}
	return retBool;
}

bool Controller::actionRight(){

	bool retBool = false;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)){//direction right
		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A)){//direction left not sellected
			retBool = true;
		}
	}
	if(sf::Joystick::isConnected(0)){
		const float STICK_RESISTANCE = 90;
		if(sf::Joystick::getAxisPosition(0,sf::Joystick::Axis::X) > STICK_RESISTANCE){
			retBool = true;
		}
	}
	return retBool;
}

bool Controller::actionUp(){

	bool retBool = false;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)){//direction up
		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S)){//direction down not sellected
			retBool = true;
		}
	}
	if(sf::Joystick::isConnected(0)){
		const float STICK_RESISTANCE = 90;
		if(sf::Joystick::getAxisPosition(0,sf::Joystick::Axis::Y) < -STICK_RESISTANCE){
			retBool = true;
		}
	}
	return retBool;
}

bool Controller::actionDown(){

	bool retBool = false;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)){//direction down
		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::W)){//direction up not sellected
			retBool = true;
		}
	}
	if(sf::Joystick::isConnected(0)){
		const float STICK_RESISTANCE = 90;
		if(sf::Joystick::getAxisPosition(0,sf::Joystick::Axis::Y) > STICK_RESISTANCE){
			retBool = true;
		}
	}
	return retBool;
}

bool Controller::actionSprint(){
	const float TRIGGER_RESISTANCE = 10;
	bool retBool = false;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
		retBool = true;
	}
	if(sf::Joystick::isConnected(0)){
		if(sf::Joystick::getAxisPosition(0,sf::Joystick::Axis::Z) < -TRIGGER_RESISTANCE){
			retBool = true;
		}
	}
	return retBool;
}

bool Controller::actionJump(){

	bool retBool = false;

	if(!actionDown()){
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)||
			sf::Keyboard::isKeyPressed(sf::Keyboard::W)||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
				retBool = true;
		}
	}
	if(sf::Joystick::isConnected(0)){
		if(sf::Joystick::isButtonPressed(0,controllerMap[GamePadInput::A])){
			retBool = true;
		}
	}

	if(!retBool){
		actionHeld[Controller::ActionType::Jump] = false;
	}
	else if(actionHeld[Controller::ActionType::Jump]){
		retBool = false;
	}
	else{
		actionHeld[Controller::ActionType::Jump] = true;
	}

	return retBool;
}

bool Controller::actionZoomOut(){

	bool retBool = false;


	if(sf::Keyboard::isKeyPressed(sf::Keyboard::L)){
			retBool = true;
	}
	if(sf::Joystick::isConnected(0)){
		if(sf::Joystick::isButtonPressed(0,controllerMap[GamePadInput::Y])){
			retBool = true;
		}
	}

	if(!retBool){
		actionHeld[Controller::ActionType::ZoomOut] = false;
	}
	else if(actionHeld[Controller::ActionType::ZoomOut]){
		retBool = false;
	}
	else{
		actionHeld[Controller::ActionType::ZoomOut] = true;
	}

	return retBool;
}

bool Controller::actionAction(){

	bool retBool = false;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
		retBool = true;
	}
	if(sf::Joystick::isConnected(0)){
		if(sf::Joystick::isButtonPressed(0,controllerMap[GamePadInput::X])){
			retBool = true;
		}
	}
	return retBool;
}

bool Controller::actionInventory(){

	bool retBool = false;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
		retBool = true;
	}
	if(sf::Joystick::isConnected(0)){
		if(sf::Joystick::isButtonPressed(0,controllerMap[GamePadInput::SELECT])){
			retBool = true;
		}
	}

	if(!retBool){//no inventory key is pressed
		actionHeld[Controller::ActionType::ToggleInventory] = false;
	}
	//inventory key is pressed and was held from the last frame
	else if(actionHeld[Controller::ActionType::ToggleInventory]){
		retBool = false;
	}
	else{
		actionHeld[Controller::ActionType::ToggleInventory] = true;
	}

	return retBool;
}

bool Controller::actionMenu(){

	bool retBool = false;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
		retBool = true;
	}
	if(sf::Joystick::isConnected(0)){
		if(sf::Joystick::isButtonPressed(0,controllerMap[GamePadInput::START])){
			retBool = true;
		}
	}

	if(!retBool){//no inventory key is pressed
		actionHeld[Controller::ActionType::ToggleMenu] = false;
	}
	//inventory key is pressed and was held from the last frame
	else if(actionHeld[Controller::ActionType::ToggleMenu]){
		retBool = false;
	}
	else{
		actionHeld[Controller::ActionType::ToggleMenu] = true;
	}

	return retBool;
}

bool Controller::actionMenuSelect(){
	bool retBool = false;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
		retBool = true;
	}
	if(sf::Joystick::isConnected(0)){
		if(sf::Joystick::isButtonPressed(0,controllerMap[GamePadInput::A])){
			retBool = true;
		}
	}

	if(!retBool){
		actionHeld[Controller::ActionType::MenuSelect] = false;
	}
	else if(actionHeld[Controller::ActionType::MenuSelect]){
		retBool = false;
	}
	else{
		actionHeld[Controller::ActionType::MenuSelect] = true;
	}

	return retBool;
}

bool Controller::actionMenuReturn(){
	bool retBool = false;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
		retBool = true;
	}
	if(sf::Joystick::isConnected(0)){
		if(sf::Joystick::isButtonPressed(0,controllerMap[GamePadInput::B])){
			retBool = true;
		}
	}

	if(!retBool){
		actionHeld[Controller::ActionType::MenuReturn] = false;
	}
	else if(actionHeld[Controller::ActionType::MenuReturn]){
		retBool = false;
	}
	else{
		actionHeld[Controller::ActionType::MenuReturn] = true;
	}

	return retBool;
}

bool Controller::dirrectionKeyPushed(){

	bool retBool = false;
	if (actionLeft() || actionRight())
	{
		retBool = true;
	}
	return retBool;
}

bool Controller::actionLeftOnce(){//doesn't return for held keys
	bool retBool = actionLeft();

	if(!retBool){
		actionHeld[Controller::ActionType::Left] = false;
	}
	else if(actionHeld[Controller::ActionType::Left]){
		retBool = false;
	}
	else{
		actionHeld[Controller::ActionType::Left] = true;
	}

	return retBool;
}

bool Controller::actionRightOnce(){//doesn't return for held keys
	bool retBool = actionRight();

	if(!retBool){
		actionHeld[Controller::ActionType::Right] = false;
	}
	else if(actionHeld[Controller::ActionType::Right]){
		retBool = false;
	}
	else{
		actionHeld[Controller::ActionType::Right] = true;
	}

	return retBool;
}

bool Controller::actionLevelLeft(){
	bool retBool = false;
	if(sf::Joystick::isButtonPressed(0,controllerMap[GamePadInput::LEFT_BUMPER])){
		if(!actionHeld[Controller::ActionType::LevelLeft]){
			retBool = true;
		}
		actionHeld[Controller::ActionType::LevelLeft] = true;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || sf::Keyboard::isKeyPressed(sf::Keyboard::LBracket)){
		if(!actionHeld[Controller::ActionType::LevelLeft]){
			retBool = true;
		}
		actionHeld[Controller::ActionType::LevelLeft] = true;
	}
	else{
		actionHeld[Controller::ActionType::LevelLeft] = false;
	}
	return retBool;
}

bool Controller::actionLevelRight(){
	bool retBool = false;
	//if(sf::Joystick::isButtonPressed(0,controllerMap[GamePadInput::RIGHT_BUMPER])){
	//	if(!actionHeld[Controller::ActionType::LevelRight]){
	//		retBool = true;
	//	}
	//	actionHeld[Controller::ActionType::LevelRight] = true;
	//}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) || sf::Keyboard::isKeyPressed(sf::Keyboard::RBracket)){
		if(!actionHeld[Controller::ActionType::LevelRight]){
			retBool = true;
		}
		actionHeld[Controller::ActionType::LevelRight] = true;
	}
	else{
		actionHeld[Controller::ActionType::LevelRight] = false;
	}
	return retBool;
}

bool Controller::actionToggleLevel()
{
	bool retBool = false;
	if(sf::Joystick::isButtonPressed(0,controllerMap[GamePadInput::RIGHT_BUMPER])){
		if(!actionHeld[Controller::ActionType::LevelToggle]){
			retBool = true;
		}
		actionHeld[Controller::ActionType::LevelToggle] = true;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)){
		if(!actionHeld[Controller::ActionType::LevelToggle]){
			retBool = true;
		}
		actionHeld[Controller::ActionType::LevelToggle] = true;
	}
	else{
		actionHeld[Controller::ActionType::LevelToggle] = false;
	}
	return retBool;
}

list<Controller::GamePadInput> Controller::getControllerInput(){
	//Get a list of all current game pad inputs 
	list<Controller::GamePadInput> inputList;
	sf::Joystick::update();
	const float TRIGGER_RESISTANCE = 10;
	const float STICK_RESISTANCE = 90;
	const float D_PAD_RESISTANCE = 100;//MUST BE 100

	if(sf::Joystick::isConnected(0)){

		if(sf::Joystick::isButtonPressed(0,controllerMap[GamePadInput::A])){
			inputList.push_back(GamePadInput::A);
		}
		if(sf::Joystick::isButtonPressed(0,controllerMap[GamePadInput::B])){
			inputList.push_back(GamePadInput::B);
		}
		if(sf::Joystick::isButtonPressed(0,controllerMap[GamePadInput::X])){
			inputList.push_back(GamePadInput::X);
		}
		if(sf::Joystick::isButtonPressed(0,controllerMap[GamePadInput::Y])){
			inputList.push_back(GamePadInput::Y);
		}

		if(sf::Joystick::isButtonPressed(0,controllerMap[GamePadInput::LEFT_BUMPER])){
			inputList.push_back(GamePadInput::LEFT_BUMPER);
		}
		if(sf::Joystick::isButtonPressed(0,controllerMap[GamePadInput::RIGHT_BUMPER])){
			inputList.push_back(GamePadInput::RIGHT_BUMPER);
		}
		if(sf::Joystick::getAxisPosition(0,sf::Joystick::Axis::Z) > TRIGGER_RESISTANCE){
			inputList.push_back(GamePadInput::LEFT_TRIGGER);
		}
		if(sf::Joystick::getAxisPosition(0,sf::Joystick::Axis::Z) < -TRIGGER_RESISTANCE){
			inputList.push_back(GamePadInput::RIGHT_TRIGGER);
		}

		if(sf::Joystick::isButtonPressed(0,controllerMap[GamePadInput::LEFT_STICK])){
			inputList.push_back(GamePadInput::LEFT_STICK);
		}
		if(sf::Joystick::isButtonPressed(0,controllerMap[GamePadInput::RIGHT_STICK])){
			inputList.push_back(GamePadInput::RIGHT_STICK);
		}

		if(sf::Joystick::isButtonPressed(0,controllerMap[GamePadInput::START])){
			inputList.push_back(GamePadInput::START);
		}
		if(sf::Joystick::isButtonPressed(0,controllerMap[GamePadInput::SELECT])){
			inputList.push_back(GamePadInput::SELECT);
		}

		if(sf::Joystick::getAxisPosition(0,sf::Joystick::PovX) == D_PAD_RESISTANCE){
			inputList.push_back(GamePadInput::D_PAD_UP);
		}
		else if(sf::Joystick::getAxisPosition(0,sf::Joystick::PovX) == -D_PAD_RESISTANCE){
			inputList.push_back(GamePadInput::D_PAD_DOWN);
		}
		else if(sf::Joystick::getAxisPosition(0,sf::Joystick::PovY) == D_PAD_RESISTANCE){
			inputList.push_back(GamePadInput::D_PAD_RIGHT);
		}
		else if(sf::Joystick::getAxisPosition(0,sf::Joystick::PovY) == -D_PAD_RESISTANCE){
			inputList.push_back(GamePadInput::D_PAD_LEFT);
		}

		if(sf::Joystick::getAxisPosition(0,sf::Joystick::Axis::X) < -STICK_RESISTANCE){
			inputList.push_back(GamePadInput::LEFT_STICK_LEFT);
		}
		else if(sf::Joystick::getAxisPosition(0,sf::Joystick::Axis::X) > STICK_RESISTANCE){
			inputList.push_back(GamePadInput::LEFT_STICK_RIGHT);
		}
		if(sf::Joystick::getAxisPosition(0,sf::Joystick::Axis::Y) < -STICK_RESISTANCE){
			inputList.push_back(GamePadInput::LEFT_STICK_UP);
		}
		else if(sf::Joystick::getAxisPosition(0,sf::Joystick::Axis::Y) > STICK_RESISTANCE){
			inputList.push_back(GamePadInput::LEFT_STICK_DOWN);
		}

		if(sf::Joystick::getAxisPosition(0,sf::Joystick::Axis::U) < -STICK_RESISTANCE){
			inputList.push_back(GamePadInput::RIGHT_STICK_LEFT);
		}
		else if(sf::Joystick::getAxisPosition(0,sf::Joystick::Axis::U) > STICK_RESISTANCE){
			inputList.push_back(GamePadInput::RIGHT_STICK_RIGHT);
		}
		if(sf::Joystick::getAxisPosition(0,sf::Joystick::Axis::R) < -STICK_RESISTANCE){
			inputList.push_back(GamePadInput::RIGHT_STICK_UP);
		}
		else if(sf::Joystick::getAxisPosition(0,sf::Joystick::Axis::R) > STICK_RESISTANCE){
			inputList.push_back(GamePadInput::RIGHT_STICK_DOWN);
		}
	}
	return inputList;
}

bool Controller::keyPressedOnce(sf::Keyboard::Key key){
	bool retBool = false;
	if(sf::Keyboard::isKeyPressed(key)){
		if(!keyHeld[key]){
			keyHeld[key] = true;
			retBool = true;
		}
	}
	else{
		keyHeld[key] = false;
	}

	return retBool;
}
	
bool Controller::actionUpOnce()
{
	bool retBool = actionUp();
	if(!retBool){
		actionHeld[Controller::ActionType::Up] = false;
	}
	else if(actionHeld[Controller::ActionType::Up]){
		retBool = false;
	}
	else{
		actionHeld[Controller::ActionType::Up] = true;
	}
	return retBool;
}
	
bool Controller::actionDownOnce()
{
	bool retBool = actionDown();
	if(!retBool){
		actionHeld[Controller::ActionType::Down] = false;
	}
	else if(actionHeld[Controller::ActionType::Down]){
		retBool = false;
	}
	else{
		actionHeld[Controller::ActionType::Down] = true;
	}
	return retBool;
}