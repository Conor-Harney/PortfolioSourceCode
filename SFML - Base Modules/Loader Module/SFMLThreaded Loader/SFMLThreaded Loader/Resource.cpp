#include "Resource.h"


Resource::Resource(void)
{
}


Resource::~Resource(void)
{
}

Resource::Resource_Type Resource::type()
{
	return m_type;
}
	
std::string Resource::name()
{
	return m_name;
}
