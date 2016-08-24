#include "KeyValuePairs.h"
#include "GameLogger.h"
#include "LogMsgType.h"
#include <iostream>

KeyValuePairs::KeyValuePairs()
{

}

KeyValuePairs::~KeyValuePairs()
{

}

bool KeyValuePairs::IsFull() const
{
	if (m_numKeys == maxKeys) 
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool KeyValuePairs::ContainsKey(const char * const key) const
{
	for (int j = 0; j < m_numKeys; ++j)
	{
		if (strcmp(m_kvPairs[j].m_key, key) == 0)
		{
			return true;
		}
	}
	return false;
}

bool KeyValuePairs::AddUnique(const char * const key, const char * const value)
{
	if (ContainsKey(key)) {
		GameLogger::Log(LogMsgType::Warning, "AddUnique: Key [%s] already exists, skipping.", key);
		return false;
	}
	else
	{
		//GameLogger::Log(LogMsgType::Info, "KeyPair [%s] added\n", key);
		AddKeyValue(key, value);
		return true;
	}
}



const char * KeyValuePairs::GetValueForKey(const char * const key) const
{
	if (ContainsKey(key))
	{
		for (int j = 0; j < m_numKeys; ++j)
		{
			if (strcmp(m_kvPairs[j].m_key, key)==0)
			{
				return m_kvPairs[j].m_value;
			}
		}
	}
	return nullptr;
}

bool KeyValuePairs::AddKeyValue(const char * const key, const char * const value)
{
	if (IsFull()) 
	{
		GameLogger::Log(LogMsgType::Warning, "AddKeyValue: m_kvPairs is full, key [%s] not added.", key);
		return false;
	}
	
	m_kvPairs[m_numKeys] = KeyValuePair{ key,value };
	m_numKeys++;
	return false;
}

std::ostream & operator<<(std::ostream & os, KeyValuePairs & kvps)
{
	
	os << "Begin KeyValuePairs\n";
	for (int j = 0; j < kvps.m_numKeys; ++j)
	{
		os << "\t" << kvps.m_kvPairs[j] << "\n";
	}
	os << "End KeyValuePairs\n";
	return os;
}
