#pragma once
#include <string>
#include <map>
#include <vector>
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <set>

using namespace std;

class AnimationFSM
{

public:
	AnimationFSM(void);
	~AnimationFSM(void);
	enum AnimationState
	{
		Idle,//1
		Walking,//2
		Running,//3
		Jumpig,//4
		Falling,//5
		Landing,//6
		Climbing,//7
		PressingButton,//8
		PushingLeaverUp,//9
		PullingLeaverDown//10
	};
	enum Direction
	{
		Front,
		Back,
		Left,
		Right
	};
	void update(sf::Time timeElasped, sf::Keyboard keyboardInput);
	set<AnimationState, Direction> getStateAndDir();

private:
	AnimationState m_CurrentState;
	Direction m_CurrentDirection;
	float m_TimeLeftInAnimation;
	int stateToNum(AnimationState stateToGet);
	AnimationState numToState(int numberToGet);

	void init();

	void generateState(sf::Keyboard keyboardInput);
	
	void setState(AnimationState newState, Direction newDirection);

	void setupAnimationTimes();
	std::map<AnimationState, float> animationStateKeyLockTime;

	std::map<AnimationState, AnimationState[]> possibleTransitions;
	void addConnection(AnimationState fromAnimation, AnimationState toAnimation);

	bool checkArrowKeysPressed();
	
};

