#ifndef KEYVALUEPAIRS_H
#define KEYVALUEPAIRS_H
// Kyle St.Amant
// 5/5/2016
// KeyValuePairs.h
// Class that holds a collection/database of key-value pairs

#include "KeyValuePair.h"
#include <ostream>

class KeyValuePairs
{
public: // ctor & dtor
	KeyValuePairs();
	~KeyValuePairs();

public: // public methods
	bool IsFull() const;                      // returns true if no room left for new keys
	bool ContainsKey(const char* const key) const; // return true if key is found

												   // log warning and return false if already contains key (NOTE: calls ContainsKey())
												   // otherwise adds the kvp and returns true (NOTE: calls AddKeyValue())
	bool AddUnique(const char* const key, const char* const value);

	const char* GetValueForKey(const char* const key) const; // return nullptr if key not found

	//GetPrintKeys
	//const * const KeyValuePair GetPrintKeys[]();
	friend std::ostream& operator<<(std::ostream& os, KeyValuePairs& kvps);

private: // private methods
		 // log warning and return false if collection is full
		 // otherwise add the kvp and return true
	bool AddKeyValue(const char* const key, const char* const value);

	/*const KeyValuePair GetKeyValPair(const char *)*/

private: // private data
	static const int maxKeys = 150;
	int              m_numKeys = 0;
	KeyValuePair     m_kvPairs[maxKeys];
};

// nicely prints out the entire list of keys. Begin KeyValuePairs / End KeyValuePairs
std::ostream& operator<<(std::ostream& os, KeyValuePairs& kvps);

#endif // ndef KEYVALUEPAIRS_H
