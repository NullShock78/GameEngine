#ifndef CONFIGREADER_H_
#define CONFIGREADER_H_


// Kyle St.Amant
// 5/6/2016
// ConfigReader.h
// Class that reads in a configuration file and stores
// the key-value pairs that it finds there



#include "KeyValuePairs.h"
#include <iostream>
#include <fstream>
#include <functional>
//ENGINE_TEMPLATE template class ENGINE_SHARED std::basic_filebuf<char, std::char_traits<char>>;
//ENGINE_TEMPLATE template class ENGINE_SHARED std::basic_ifstream<char, std::char_traits<char>>;

class ConfigReader
{
public:
	ConfigReader();
	~ConfigReader();

public: // public methods
	bool Initialize(const char* const filename, const char* const key = nullptr);
	bool Shutdown();

	bool ReloadConfigVals();

	bool IsFull() const;                           // returns true if no room left for new keys
	bool ContainsKey(const char* const key) const; // return true if key is found
	bool ContainsRequiredKey(const char* const key) const; // return true if key is found
												   // return false if key already found, otherwise add the KVP and return true
	bool AddUnique(const char* const key, const char* const value);

	// returns true if key found and fills in value
	bool GetStringForKey(const char* const key, const char*& outValue);
	bool GetIntForKey(const char* const key, int & outValue);
	bool GetFloatForKey(const char* const key, float & outValue);
	void GetFloatForKey(const char* const key, float & outValue, float defaultVal);
	bool GetFloatsForKey(const char * key, int numFloats, float * values);
	bool GetBoolForKey(const char* const key, bool & outValue, bool defaultVal);
	bool DupStringForKey(const char * const key, char * outValue, int bufferLen, int & outCount);

	bool RegisterForOnUpdate(std::function <void()> func);

private: //Private methods.
	const char * m_filename;
	int m_numInfoFuncs{ -1 };

	std::function <void()> m_updateInfoFuncs[50];

	//Reads file, high level
	bool ReadFile(const char * const filename);

	//Processes a single line
	bool ProcessLine(const char * line);
	//bool ProcessWord(char * buffer, const int bufSize, const char * const line);
	bool ProcessKey(char * buffer, const int bufSize, const char * & line);
	bool ProcessVal(char * buffer, const int bufSize, const char * & line);
	bool CopyToEnd(char * buffer, int &bufSize, const char * &line, char endChar = ' ', bool needsEnd = false, char tab = '\t');
	//Skips blanks
	int SkipWhiteSpace(const char * &line);
	int Skip(const char * line, char skipChar);
	bool CheckComment(const char * line);
	//bool CheckEnd(const char * buffer);
	
	//Checks if there's a key
	//const char * FindKey(char * keyBuff, int bufSize, const char * bufPtr);

	friend std::ostream& operator<<(std::ostream& os, ConfigReader& kvps);
	
private:
	std::ifstream m_myFile;
	KeyValuePairs m_db; // database of kvps
	int m_lines = 0;
};

// nicely prints out the entire list of keys. Begin KeyValuePairs / End KeyValuePairs
std::ostream& operator<<(std::ostream& os, ConfigReader& kvps);

#endif // ndef CONFIGREADER_H_

