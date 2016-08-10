#include "ConfigReader.h"
//#include<iostream>
//#include <fstream>
#include<string.h>
#include "GameLogger.h"
#include <cstdlib>
#include <sstream>
std::ifstream m_myFile;
ConfigReader::ConfigReader()
{
}


ConfigReader::~ConfigReader()
{
	delete[] m_filename;
}

bool ConfigReader::Initialize(const char * const filename, const char * const /*key*/)
{
	m_filename = _strdup(filename);

	if (filename == nullptr) 
	{
		GameLogger::Log(LogMsgType::cFatalError, "nullptr passed into ConfigReader filename.");
		//GameLogger::Shutdown();
		return false;
	}
	if (!ReadFile(filename)) {
		//TODO: add log here
		GameLogger::Log(LogMsgType::cFatalError, "Config reader failed to open [%s] for reading", filename);
		Shutdown();
		return false;

	}
	std::cout << m_db;
	GameLogger::Log(LogMsgType::cInfo, "Config reader opened [%s] for reading!", filename);
	return true;
	
}

bool ConfigReader::Shutdown()
{
	if (m_myFile.is_open())
	{
		m_myFile.close();
	}

	if (m_myFile.is_open()) 
	{
		GameLogger::Log(LogMsgType::Error, "ConfigReader failed to shut down");
	}
	else 
	{
		GameLogger::Log(LogMsgType::Process, "ConfigReader shut down successfully");
	}


	return true;
}

bool ConfigReader::ReloadConfigVals()
{

	//m_myFile.

	m_db = KeyValuePairs{};
	if (!ReadFile(m_filename)) {
		//TODO: add log here
		GameLogger::Log(LogMsgType::FatalError, "Config reader failed to open [%s] for reading", m_filename);
		Shutdown();
		return false;

	}
	std::cout <<"Config file ["<< m_filename << "] reloaded!\n"  << m_db;

	for (int j = 0; j <= m_numInfoFuncs; ++j)
	{
		m_updateInfoFuncs[j]();
	}
	return true;

}

bool ConfigReader::IsFull() const
{
	return m_db.IsFull();
	//return false;
}

bool ConfigReader::ContainsKey(const char * const key) const
{
	return m_db.ContainsKey(key);
}

bool ConfigReader::ContainsRequiredKey(const char * const key) const
{
	GameLogger::Log(LogMsgType::FatalError, "Required key %s not found", key);
	return m_db.ContainsKey(key);
}

bool ConfigReader::AddUnique(const char * const key, const char * const value)
{
	//if (ContainsKey(key)) return false;
	return m_db.AddUnique(key, value);
}

bool ConfigReader::GetStringForKey(const char * const key, const char *& outValue)
{
	if (!ContainsKey(key)) { GameLogger::Log(LogMsgType::cFatalError, "Key Not Found"); return false; }
	outValue = m_db.GetValueForKey(key);
	return true;
}

bool ConfigReader::GetIntForKey(const char * const key, int & outValue)
{
	if (!ContainsKey(key)) return false;
	const char * valToParse;
	GetStringForKey(key, valToParse);
	outValue = std::atoi(valToParse);

	return true;
}

bool ConfigReader::GetFloatForKey(const char * const key, float & outValue)
{
	if (!ContainsKey(key)) return false;
	const char * valToParse;
	GetStringForKey(key, valToParse);
	outValue = (float)std::atof(valToParse);

	return true;
}

void ConfigReader::GetFloatForKey(const char * const key, float & outValue, float defaultVal)
{
	if (!ContainsKey(key))
	{
	GameLogger::Log(LogMsgType::Warning, "Key %s does not exist, using default val %d", key, defaultVal);
	outValue = defaultVal;
	}

	const char * valToParse;
	GetStringForKey(key, valToParse);
	outValue = (float)std::atof(valToParse);


}


bool ConfigReader::GetFloatsForKey(const char * key, int numFloats, float * values)
{

	if (!ContainsKey(key)) {
		GameLogger::Log(LogMsgType::cFatalError, "ConfigReader::GetFloatsForKey(): Key %s does not exist, aborting.", key);
		return false;
	}

	if (numFloats == 0)
	{
		GameLogger::Log(LogMsgType::cFatalError, "ConfigReader::GetFloatsForKey(): 0 floats requested for key %s, aborting.", key);
		return false;
	}

	const char * valToParse;
	GetStringForKey(key, valToParse);

	std::istringstream strStream = std::istringstream(valToParse);

	for (int j = 0; j < numFloats; j++)
	{
		std::string temp;
		if (!(strStream >> temp))
		{
			GameLogger::Log(LogMsgType::cFatalError, "ConfigReader::GetFloatsForKey(): Key %s: not enough floats! [%d] floats requested, [%d] floats found. aborting.", key, numFloats, j - 1);
			return false;
		}
		//const char * val = temp;

		*values = (float)std::atof(temp.c_str());
		++values;

	}
	return true;
}

bool ConfigReader::GetBoolForKey(const char * const key, bool & outValue, bool defaultVal)
{
	if (!ContainsKey(key)) {
		GameLogger::Log(LogMsgType::Warning, "Key %s does not exist, using default val %d", key, defaultVal);
		outValue = defaultVal;
		return true;
	}
	const char * valToParse;
	GetStringForKey(key, valToParse);

	if (0 == std::strcmp(valToParse, "true")) 
	{
		outValue = true;
	}
	else if (0 == std::strcmp(valToParse, "false"))
	{
		outValue = false;
	}
	else
	{
		outValue = defaultVal;
	}

	return true;
}

bool ConfigReader::DupStringForKey(const char * const key, char * outValue, int bufferLen, int & outCount)
{
		if (!ContainsKey(key)) return false;
		const char * temp = m_db.GetValueForKey(key);
		const char * tempPtr = temp;
		int len = 0;
		while (*tempPtr != '\0')
		{
			++len;
			++tempPtr;
		}

		if (len > bufferLen)
		{
			GameLogger::Log(LogMsgType::cFatalError, "ConfigReader::DupStringForKey(): len[%d] > bufferLen[%d]", len, bufferLen);
			return false;
		}

		outCount += len;
		tempPtr = temp;
		while (*tempPtr != '\0')
		{
			*outValue = *tempPtr;
			++outValue;
			++tempPtr;
		}
		return true;

}

bool ConfigReader::RegisterForOnUpdate(std::function<void()> func)
{
	++m_numInfoFuncs;
	m_updateInfoFuncs[m_numInfoFuncs] = func;
	return true;
}



//Working on breaking down in other file, using the one that works for now
bool ConfigReader::ReadFile(const char * const filename)
{
	//File to read in
	
	//Attempt to open path
	m_myFile.open(filename, std::ios::in);
	
	if (!m_myFile)
	{
		//GameLogger::Log(LogMsgType::FatalError, "ConfigReader failed to open the file [%s] for reading, check the path.\n", filename);
		//GameLogger::Log(LogMsgType::FatalError, "Failed to open file");
		return false;
	}
	GameLogger::Log(LogMsgType::Process, "ConfigReader opened [%s] successfully", filename);
	GameLogger::Log(LogMsgType::Info, "ConfigReader initialized successfully");

	while (!m_myFile.eof())
	{
		const int bufSize = 400;
		//char buffer of 400, initialized with all 0s
		char readBuffer[bufSize]{ 0 };
		m_myFile.getline(readBuffer, bufSize);
		ProcessLine(readBuffer);
	}
	m_myFile.close();
	return true;
}



//False means key val wasn't created
bool ConfigReader::ProcessLine(const char * line)
{	
	++m_lines;
	//Ptr to buffer
	//const char * linePtr = line;
	const char * &linePtr2 = line;
	if (*linePtr2 == 0) return false;

	const int keyAndValBuffSize = 50;
	char keyBuffer[keyAndValBuffSize]{ 0 };
	char valBuffer[keyAndValBuffSize]{ 0 };

	//nst char* keyPtr = //FindKey(key, keyAndValBuffSize, linePtr);
	
	int ptrMove = SkipWhiteSpace(linePtr2);
	//linePtr += ptrMove;

	if (*linePtr2 == 0)
	{
		return false;
	}
	else if (CheckComment(linePtr2))
	{
		return false;
	}
	else if (ProcessKey(keyBuffer, keyAndValBuffSize, linePtr2))
	{
		//GameLogger::Log(LogMsgType::Error)
		//const char * linePtr2 = linePtr;
		ptrMove = SkipWhiteSpace(linePtr2);

		//std::cout << linePtr2 << "\n";
		//linePtr += ptrMove;
		if (CheckComment(linePtr2))
		{
			//std::cout << "Comment\n";
			return false;
		}
		else if (ProcessVal(valBuffer, keyAndValBuffSize, linePtr2))
		{
			if (!IsFull()) {
				if(AddUnique(keyBuffer, valBuffer))
				{
				GameLogger::Log(LogMsgType::Info, "Valid KVP [%s] [%s] added", keyBuffer, valBuffer);

					return true;
				}
				else
				{
					GameLogger::Log(LogMsgType::Info, "KVP [%s] [%s] was unable to be added", keyBuffer, valBuffer);
					return false;
				}
			}
			else
			{
				GameLogger::Log(LogMsgType::FatalError, "KeyPair list is full");
				Shutdown();
			}


		}
	}
	else
	{
		//Do nothing
	}
		
	

	
	//strcat_s(key, keyAndValBuffSize ,);

	return false;
}



bool ConfigReader::ProcessKey(char * buffer, const int bufSize, const char * &line)
{
	//const char * linePtr = line;
	bool result = true;

	int bufSizeLeft = bufSize;

	if (*line == '\"')
	{
		++line;
		result = CopyToEnd(buffer, bufSizeLeft, line, '\"', true);

		if (!result)
		{
			if (CheckComment(line))
			{
				GameLogger::Log(LogMsgType::Error, "Key on line [%d] in the config file has an unclosed (\") and is followed by a comment.", m_lines);
			}
			else if (bufSizeLeft < 1) 
			{
				GameLogger::Log(LogMsgType::Error, "Key on line [%d] in the config file exceeds bufSize[%d].", m_lines, bufSize);
			}
			else
			{
				GameLogger::Log(LogMsgType::Error, "Key on line [%d] in the config file has an unclosed (\").", m_lines);
			}

		}

	}
	else
	{
		result = CopyToEnd(buffer, bufSizeLeft, line, ' ', true);

		if (!result)
		{
			if (CheckComment(line))
			{
				GameLogger::Log(LogMsgType::Error, "Key on line [%d] in the config file has a key followed by a comment.", m_lines);
			}
			else if (bufSizeLeft < 1)
			{
				GameLogger::Log(LogMsgType::Error, "Key on line [%d] in the config file has a key exceeding bufSize[%d].", m_lines, bufSize);
			}
			else
			{
				GameLogger::Log(LogMsgType::Error, "Key on line [%d] in the config file has no value.", m_lines);
			}

		}

	}

	

	return result;
}

bool ConfigReader::ProcessVal(char * buffer, const int bufSize, const char * & line)
{
//	const char * linePtr = line;
	bool result = true;

	int bufSizeLeft = bufSize;

	if (*line == '\"')
	{
		++line;
		result = CopyToEnd(buffer, bufSizeLeft, line, '\"', true);

		if (!result)
		{
			if (CheckComment(line))
			{
				GameLogger::Log(LogMsgType::Error, "Val on line [%d] in the config file has an unclosed (\") and is followed by a comment.", m_lines);
			}
			else if (bufSizeLeft < 1)
			{
				GameLogger::Log(LogMsgType::Error, "Val on line [%d] in the config file has a val exceeding bufSize[%d].", m_lines, bufSize);
			}
			else
			{
				GameLogger::Log(LogMsgType::Error, "Val on line [%d] in the config file has an unclosed (\").", m_lines);
			}

		}

	}
	else
	{
		result = CopyToEnd(buffer, bufSizeLeft, line);
		const char * lineExtraCheckPtr = line;
		if (!result)
		{
			if (bufSizeLeft < 1)
			{
				GameLogger::Log(LogMsgType::Error, "Val on line [%d] in the config file has a key exceeding bufSize[%d], fix config file.", m_lines, bufSize);
			}
			else
			{
				GameLogger::Log(LogMsgType::Error, "Val on line [%d] in the config file exceeds val bufferSize.", m_lines);
			}

		}
		else 
		{
			SkipWhiteSpace(lineExtraCheckPtr);
			if (!CheckComment(lineExtraCheckPtr) && *lineExtraCheckPtr != 0) {
				GameLogger::Log(LogMsgType::Error, "ProcessVal: Line [%d] of config file has multiple values, but no quotes.", m_lines);
				result = false;
			}
		}

	}



	return result;
}

//Returns true if no issues.
bool ConfigReader::CopyToEnd(char * const buffer, int &bufSize_REF, const char * & line_REF, char endChar, bool needsEnd, char tab)
{


	int bufSizeLeft = bufSize_REF;
	char * bufferPtr = buffer;
	const char * & linePtr = line_REF;
	bool quoteWarning = false;

	while (*linePtr != endChar)
	{
		if (!quoteWarning && !needsEnd && endChar != '"' && *linePtr == '"')
		{
			GameLogger::Log(LogMsgType::Warning, "End quote without opening quote for val detected on line [%d].", m_lines);
			quoteWarning = true;
		}

		if (!needsEnd && *linePtr == tab)
		{
			return true;
		}
		else if (needsEnd && isspace(endChar) && isspace(*linePtr))
		{
			return true;
		}
		
		if (!needsEnd && CheckComment(linePtr))
		{
			return true;
		}
		if (needsEnd && CheckComment(linePtr))
		{
			return false;
		}
		else if (needsEnd && *linePtr == 0) 
		{
			//Quote not closed
			//GameLogger::Log(LogMsgType::Error, "[%s] needs to be closed\n", line);
			return false;
		}
		else if (!needsEnd && *linePtr == 0)
		{
			//Quote not closed
			//GameLogger::Log(LogMsgType::Error, "[%s] needs to be closed\n", line);
			return true;
		}
		else if (bufSizeLeft < 1) 
		{
			//GameLogger::Log(LogMsgType::Error, "CopyToEnd -  bufSize exceeded\n");
			return false;
		}
		*bufferPtr = *linePtr;
		++bufferPtr;
		++linePtr;
		--bufSizeLeft;
	}

	/*if (needsEnd && len == 0 && endChar == '"') {
		return 
	}*/
	++linePtr;

	return true;
}

int ConfigReader::SkipWhiteSpace(const char * & line)
{
	int posAdded = 0;

	//const char * linePtr = line;


	while (isspace(*line) )
	{
		++line;
		++posAdded;
	}

	return posAdded;
}

int ConfigReader::Skip(const char * line, char skipChar)
{
	int posAdded = 0;

	const char * linePtr = line;


	while (*linePtr == skipChar)
	{
		++linePtr;
		++posAdded;
	}

	return posAdded;
}

bool ConfigReader::CheckComment(const char * line)
{

	if (*line == '/')
	{
		if (*(line + 1) == '/')
		{
			//Comment, End of the line
			return true;
		}
	}
	
	return false;
}


std::ostream & operator<<(std::ostream & os, ConfigReader & kvps)
{
	return os << kvps.m_db;
}
