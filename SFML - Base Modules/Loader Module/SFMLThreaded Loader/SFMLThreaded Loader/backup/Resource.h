#pragma once
#include "SFML/Graphics.hpp" 
class Resource
{
public:
	enum Resource_Type
	{
		Null,
		Sound,
		Music,
		Image,
		Spritesheet
	};
	Resource_Type type();
	std::string name();

protected:
	Resource(void);
	~Resource(void);
	
	std::string m_name;
	Resource_Type m_type;
};

