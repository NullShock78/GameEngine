#ifndef KEYVALUEPAIR_H
#define KEYVALUEPAIR_H

// Kyle St.Amant
// 5/4/2016
// KeyValuePair.h
// Simple class to hold keys and values in strings

#include <ostream>

class KeyValuePair
{
public:

	KeyValuePair();
	KeyValuePair(const char* const key, const char* const value);
	~KeyValuePair();
public: // data members
	static const int maxChars = 48;
	char m_key[maxChars]{ 0 };
	char m_value[maxChars]{ 0 };
	
};

// {KVP} [Key] [Value]
std::ostream& operator<<(std::ostream& os, KeyValuePair& kvp);

#endif // ndef KEYVALUEPAIR_H_
