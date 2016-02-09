#pragma once
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <set>

class Camera
{
public:
	Camera(const sf::Vector2f* LEVELDIMENTIONS);
	~Camera(void);
	void update(sf::Vector2f playerPos, sf::Time timeElasped);
	sf::View getView();
	void toggleZoom();
	void toggleZoom(float waitTime);
	float* getSizeMultiplier();
	sf::Vector2f* getPosition();
	void setZoomPercent(float percent);
	void jumpToZoom(float percent, sf::Vector2f targetPos);
	void setUpSlowZoom(float percentTo, sf::Vector2f pointTo, float stayTime);
	void toggleSnapZoom();

private:
	sf::View followPlayer;
	const sf::Vector2f* LEVEL_DIMENTIONS;
	sf::Vector2f m_Size;
	bool zoomActive;
	bool zooming;

	void zoomTo(sf::Time timeElasped);
	float percentToZoomTo;
	float percentZoomingFrom;
	float timeToZoom;
	const float maxTimeToZoom;

	float m_percentZoomed;

	
	void slowZoomFunc(sf::Time timeElasped);
	float m_timeRemainingInZoom;
	sf::Vector2f m_SizeFrom;
	sf::Vector2f m_SizeTo;
	sf::Vector2f m_SizeDiffirence;
	sf::Vector2f m_CenterDiffirence;
	sf::Vector2f m_CenterFrom;
	sf::Vector2f m_PlayerPos;
	sf::Vector2f m_CurrentCenter;
	bool followingPlayer;
	float* m_sizeMultiplier;
	sf::Vector2f m_CurrentSize;
	sf::Vector2f* m_CameraPos;
	float m_ZoomPercent;
	float m_timeBeforeZoom;

};

