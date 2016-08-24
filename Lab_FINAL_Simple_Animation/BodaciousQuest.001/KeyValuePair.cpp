#include "KeyValuePair.h"
#include <string.h>
#include <iomanip>

KeyValuePair::KeyValuePair()
{
	//m_key
}

KeyValuePair::KeyValuePair(const char * const key, const char * const value)
{
	//const char * keyPtr;
	//m_key = {0};


	strcat_s(m_key, maxChars, key);
	strcat_s(m_value, maxChars, value);
}



KeyValuePair::~KeyValuePair()
{
}


std::ostream & operator<<(std::ostream & os, KeyValuePair & kvp)
{
	return os << "{KVP} [" << kvp.m_key << "] : [" << kvp.m_value << "]";
}
