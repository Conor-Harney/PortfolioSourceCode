#include "stdafx.h"
#include "AudioManager.h"
#include "dirent.h"

AudioManager* AudioManager::m_instance;

AudioManager* AudioManager::getInstance()
{
	if(m_instance == 0)
	{
		m_instance = new AudioManager();
	}
	return m_instance;
}

AudioManager::AudioManager(void)
{
	requestedThisUpdate = false;
	requestAvailible = true;
	SFXVolume = 100;
	musicAmbientVolume = 100;
	m_muted = false;
}


AudioManager::~AudioManager(void)
{
}

void AudioManager::playSoundEffect(string name){
	if(!m_muted)
	{
		if(requestAvailible){
			string tempName = name;
			tempName.append(".wav");
			//sf::Sound* tempSound = ResourceManager::getInstance()->getSfx(name);
			ResourceManager::getInstance()->getSfx(tempName)->setVolume(SFXVolume);
			ResourceManager::getInstance()->getSfx(tempName)->play();
		}
	}
	requestedThisUpdate = true;
}

void AudioManager::playAmbientSound(){

}

void AudioManager::playMusic(int trackNumber){
	if(!m_muted)
	{
		string newMusicName = "Track" + std::to_string(trackNumber);
		if(ResourceManager::getInstance()->checkMusicExists(newMusicName))
		{
			m_currentMusicName = newMusicName;
			ResourceManager::getInstance()->getMusic(m_currentMusicName)->setVolume(musicAmbientVolume);
			ResourceManager::getInstance()->getMusic(m_currentMusicName)->play();
			ResourceManager::getInstance()->getMusic(m_currentMusicName)->setLoop(true);
		}
	}
}

void AudioManager::setSfxVolume(float volume){
	SFXVolume = volume;
}

void AudioManager::setMusicVolume(float volume){
	musicAmbientVolume = volume;
	if(!m_currentMusicName.empty())
	{
		ResourceManager::getInstance()->getMusic(m_currentMusicName)->setVolume(musicAmbientVolume);
	}
}

void AudioManager::updateRequests(){
	if(!requestedThisUpdate){requestAvailible = true;}
	else{requestAvailible = false;}
	requestedThisUpdate = false;
}

void AudioManager::stopMusic()
{
	if(m_currentMusicName != ""){
		ResourceManager::getInstance()->getMusic(m_currentMusicName)->stop();
	}
}

void AudioManager::toggleMute()
{
	m_muted = (!m_muted);
	if(m_muted){
		ResourceManager::getInstance()->getMusic(m_currentMusicName)->stop();
	}
	else
	{
		ResourceManager::getInstance()->getMusic(m_currentMusicName)->play();
	}
}