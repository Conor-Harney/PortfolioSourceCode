#include "stdafx.h"
#include "Camera.h"


Camera::Camera(const sf::Vector2f* LEVELDIMENTIONS):LEVEL_DIMENTIONS(LEVELDIMENTIONS), maxTimeToZoom(1.0)
{
	m_Size = sf::Vector2f(LEVEL_DIMENTIONS->x, LEVEL_DIMENTIONS->y);
	zooming = false;
	timeToZoom = 0;
	m_CurrentCenter = sf::Vector2f(LEVEL_DIMENTIONS->x / 2, LEVEL_DIMENTIONS->y / 2);
	followingPlayer = true;
	followPlayer.setSize(m_Size);
	followPlayer.setCenter(m_CurrentCenter);
	zoomActive = false;
	m_ZoomPercent = 60;
	m_sizeMultiplier = new float(followPlayer.getSize().x / LEVEL_DIMENTIONS->x);
	m_CameraPos = new sf::Vector2f(m_CurrentCenter - (sf::Vector2f(m_CurrentSize.x / 2, m_CurrentSize.y / 2)));
	m_timeBeforeZoom = 0;
}

void Camera::update(sf::Vector2f playerPos, sf::Time timeElasped){
	m_PlayerPos = playerPos;

	slowZoomFunc(timeElasped);
	m_Size = followPlayer.getSize();
	if(!zooming && followingPlayer){
		m_CurrentCenter = playerPos;
	}

	if( m_CurrentCenter.x - (m_Size.x / 2) < 0){
		m_CurrentCenter.x = (m_Size.x / 2);
	}
	else if(m_CurrentCenter.x + (m_Size.x / 2) > LEVEL_DIMENTIONS->x){
		m_CurrentCenter.x = LEVEL_DIMENTIONS->x - (m_Size.x / 2);
	}
	if( m_CurrentCenter.y - (m_Size.y / 2) < 0){
		m_CurrentCenter.y = (m_Size.y / 2);
	}
	else if(m_CurrentCenter.y + (m_Size.y / 2) > LEVEL_DIMENTIONS->y){
		m_CurrentCenter.y = LEVEL_DIMENTIONS->y - (m_Size.y / 2);
	}

	followPlayer.setCenter(m_CurrentCenter);
	*m_CameraPos = m_CurrentCenter - (sf::Vector2f(m_CurrentSize.x / 2, m_CurrentSize.y / 2));
}


Camera::~Camera(void)
{
}

void Camera::toggleZoom(){
	zoomActive = !zoomActive;
	if(zoomActive){
		setUpSlowZoom(m_ZoomPercent, m_PlayerPos, 0);
	}else{
		setUpSlowZoom(0, sf::Vector2f(LEVEL_DIMENTIONS->x / 2, LEVEL_DIMENTIONS->y / 2), 0);
	}
}

void Camera::toggleZoom(float waitTime){
	zoomActive = !zoomActive;
	if(zoomActive){
		setUpSlowZoom(m_ZoomPercent, m_PlayerPos, waitTime);
	}else{
		setUpSlowZoom(0, sf::Vector2f(LEVEL_DIMENTIONS->x / 2, LEVEL_DIMENTIONS->y / 2), waitTime);
	}
}

sf::View Camera::getView(){
	return followPlayer;
}

void Camera::setUpSlowZoom(float percentTo, sf::Vector2f pointTo, float stayTime){
	m_timeBeforeZoom = stayTime;
	m_CenterFrom = followPlayer.getCenter();
	float m_PercentTo = percentTo;

	m_timeRemainingInZoom = maxTimeToZoom;

	m_SizeFrom = followPlayer.getSize();
	m_SizeTo   = *LEVEL_DIMENTIONS * (1 - (m_PercentTo/100));

	m_SizeDiffirence = m_SizeTo - m_SizeFrom;
	m_CenterDiffirence = pointTo - m_CenterFrom;

	if(percentTo != 0){
		followingPlayer = true;
		m_CurrentCenter = pointTo;
		zoomActive = true;
	}else{
		followingPlayer = false;
		zoomActive = false;
		m_CurrentCenter = sf::Vector2f(LEVEL_DIMENTIONS->x / 2, LEVEL_DIMENTIONS->y / 2);
	}

	zooming = true;
}

void Camera::slowZoomFunc(sf::Time timeElasped){
	if(zooming){
		if(m_timeBeforeZoom <= 0){
			if(m_timeBeforeZoom < 0){
				m_timeBeforeZoom = 0;
			}
			if(followingPlayer){
				m_CenterDiffirence = m_PlayerPos - m_CenterFrom;
			}
			m_timeRemainingInZoom -= timeElasped.asSeconds();
			float timePassed = maxTimeToZoom - m_timeRemainingInZoom;
			float percentCompleted = (timePassed / maxTimeToZoom) * 100;

			m_CurrentSize = m_SizeFrom + m_SizeDiffirence * (percentCompleted / 100);
			m_CurrentCenter = m_CenterFrom + m_CenterDiffirence * (percentCompleted / 100);

			if(percentCompleted >= 100){
				percentCompleted = 100;
				m_CurrentSize = m_SizeFrom + m_SizeDiffirence;
				m_CurrentCenter = m_CenterFrom + m_CenterDiffirence;
				zooming = false;
			}
			followPlayer.setCenter(m_CurrentCenter);
			followPlayer.setSize(m_CurrentSize);
			*m_sizeMultiplier = (followPlayer.getSize().x / LEVEL_DIMENTIONS->x);
		}
		else
		{
			m_timeBeforeZoom -= timeElasped.asSeconds();
		}
	}
}

float* Camera::getSizeMultiplier(){
	return m_sizeMultiplier;
}

sf::Vector2f* Camera::getPosition(){
	return m_CameraPos;
}

void Camera::setZoomPercent(float percent){
	m_ZoomPercent = percent;
}

void Camera::jumpToZoom(float percent, sf::Vector2f targetPos){
	m_CurrentSize = *LEVEL_DIMENTIONS * (1 - (percent / 100));
	if(percent != 0){
		followingPlayer = true;
		m_CurrentCenter = targetPos;
	}else{
		followingPlayer = false;
		zoomActive = false;
		m_CurrentCenter = sf::Vector2f(LEVEL_DIMENTIONS->x / 2, LEVEL_DIMENTIONS->y / 2);
	}
	followPlayer.setCenter(m_CurrentCenter);
	followPlayer.setSize(m_CurrentSize);
	*m_sizeMultiplier = (followPlayer.getSize().x / LEVEL_DIMENTIONS->x);
}

void Camera::toggleSnapZoom(){
	zoomActive = !zoomActive;
	if(zoomActive){
		jumpToZoom(m_ZoomPercent, m_PlayerPos);
	}else{
		jumpToZoom(0, sf::Vector2f(LEVEL_DIMENTIONS->x / 2, LEVEL_DIMENTIONS->y / 2));
	}
}