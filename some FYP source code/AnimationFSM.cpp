#include "stdafx.h"
#include "AnimationFSM.h"


AnimationFSM::AnimationFSM(void)
{
	m_CurrentState = AnimationState::Idle;
	m_CurrentDirection = Direction::Front;
	m_TimeLeftInAnimation = 0;
}

void AnimationFSM::setupAnimationTimes(){//setup the amount of seconds each animation will take
	animationStateKeyLockTime[AnimationState::Idle] = 0;
	animationStateKeyLockTime[AnimationState::Walking] = 2;
	animationStateKeyLockTime[AnimationState::Running] = 2;
	animationStateKeyLockTime[AnimationState::Jumpig] = 1;
	animationStateKeyLockTime[AnimationState::Falling] = 1;
	animationStateKeyLockTime[AnimationState::Landing] = 1;
	animationStateKeyLockTime[AnimationState::PressingButton] = 1;
	animationStateKeyLockTime[AnimationState::PullingLeaverDown] = 2;
	animationStateKeyLockTime[AnimationState::PushingLeaverUp] = 2;
}

AnimationFSM::~AnimationFSM(void)
{
	
}

int AnimationFSM::stateToNum(AnimationState stateToGet){
	int numToReturn = 0;

	switch(stateToGet){

		case(AnimationState::Idle):
			numToReturn = 1;
			break;

		case(AnimationState::Walking):
			numToReturn = 2;
			break;

		case(AnimationState::Running):
			numToReturn = 3;
			break;

		case(AnimationState::Jumpig):
			numToReturn = 4;
			break;

		case(AnimationState::Falling):
			numToReturn = 5;
			break;

		case(AnimationState::Landing):
			numToReturn = 6;
			break;

		case(AnimationState::Climbing):
			numToReturn = 7;
			break;

		case(AnimationState::PressingButton):
			numToReturn = 8;
			break;

		case(AnimationState::PushingLeaverUp):
			numToReturn = 9;
			break;

		case(AnimationState::PullingLeaverDown):
			numToReturn = 10;
			break;

		default:
			numToReturn = -1;
			break;
		
	}

	return numToReturn;
}

AnimationFSM::AnimationState AnimationFSM::numToState(int numberToGet){

	AnimationState stateToReturn;

	switch(numberToGet){
		
		case(1):
			stateToReturn = AnimationState::Idle;
			break;

		case(2):
			stateToReturn = AnimationState::Walking;
			break;

		case(3):
			stateToReturn = AnimationState::Running;
			break;

		case(4):
			stateToReturn = AnimationState::Jumpig;
			break;

		case(5):
			stateToReturn = AnimationState::Falling;
			break;

		case(6):
			stateToReturn = AnimationState::Landing;
			break;

		case(7):
			stateToReturn = AnimationState::Climbing;
			break;

		case(8):
			stateToReturn = AnimationState::PressingButton;
			break;

		case(9):
			stateToReturn = AnimationState::PushingLeaverUp;
			break;

		case(10):
			stateToReturn = AnimationState::PullingLeaverDown;
			break;

		default:
			stateToReturn = AnimationState::Idle;
			break;
		
	}

	return stateToReturn;
}

void AnimationFSM::init(){
	
}

void AnimationFSM::update(sf::Time timeElasped, sf::Keyboard keyboardInput){
	if(m_TimeLeftInAnimation >= 0){
		generateState(keyboardInput);
	}
}

void AnimationFSM::generateState(sf::Keyboard keyboardInput){
	AnimationFSM::AnimationState oldState = m_CurrentState; 
	AnimationFSM::Direction oldDirection = m_CurrentDirection;

	switch (oldState)
	{
	case AnimationFSM::Idle:

		break;
	case AnimationFSM::Walking:
		break;
	case AnimationFSM::Running:
		if (checkArrowKeysPressed())
		{
			//if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)
		}
		break;
	case AnimationFSM::Jumpig:
		break;

	case AnimationFSM::Falling:
		break;

	case AnimationFSM::Landing:
		setState(AnimationState::Idle, oldDirection);
		break;
	case AnimationFSM::Climbing:
		setState(AnimationState::Idle, oldDirection);
		break;
	case AnimationFSM::PressingButton:
		setState(AnimationState::Idle, oldDirection);
		break;
	case AnimationFSM::PushingLeaverUp:
		setState(AnimationState::Idle, oldDirection);
		break;
	case AnimationFSM::PullingLeaverDown:
		setState(AnimationState::Idle, oldDirection);
		break;
	default:
		break;
	}

}

void AnimationFSM::setState(AnimationState newState, Direction newDirection){
	m_CurrentState = newState;
	m_TimeLeftInAnimation = animationStateKeyLockTime[newState];
	m_TimeLeftInAnimation = animationStateKeyLockTime[newState];
}

bool AnimationFSM::checkArrowKeysPressed(){
	bool retBool = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)	|| 
		sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || 
		sf::Keyboard::isKeyPressed(sf::Keyboard::Up)	|| 
		sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		retBool = true;
	}

	return retBool;
}

