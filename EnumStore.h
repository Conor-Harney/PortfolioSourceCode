#pragma once
//this file stores enum-specifiers so multiple classes 
//can access them while avoiding circular dependencies
class EnumStore{
public:
	enum GAME_STATE{
		IN_GAME,
		IN_INVENTORY,
		IN_PAUSE_MENU,
		IN_MAIN_MENU,
		LOADING,
		SCOREBOARD,
		TUTORIAL,
		NAMEWRITTER
	};
	enum inventoryItem
	{
		empty,
		battery,
		torch,
		wire,
		tape,
		scissors,
		potion
	};
	enum EnvirementItemType
	{
		Pickup,
		EnvirementFixture,
		LevelEndDoor
	};
};