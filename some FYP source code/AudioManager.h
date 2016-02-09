#pragma once
#include <list>
#include <Map>
#include "SFML/Audio.hpp"
#include <memory.h>
#include "ResourceManager.h"

using namespace std;

class AudioManager
{
public:
	static AudioManager* getInstance();
	void playSoundEffect(string name);
	void playAmbientSound();
	void playMusic(int trackNumber);
	void setSfxVolume(float);
	void setMusicVolume(float); 
	void updateRequests();
	void stopMusic();
	void toggleMute();

private:
	static AudioManager* m_instance;
	AudioManager(void);
	~AudioManager(void);
	float SFXVolume;
	float musicAmbientVolume;
	std::vector<std::string> m_SFXNames;//the names of all availible sfx
	string m_currentMusicName;

	//double bools to stop repeat requests.
	bool requestAvailible;//can a sound be requested this update
	bool requestedThisUpdate;//was a sound requested this update
	bool m_muted;
};

