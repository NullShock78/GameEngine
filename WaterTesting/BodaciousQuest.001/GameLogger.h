#ifndef GAME_LOGGER_H
#define GAME_LOGGER_H

#include <fstream>
#include"LogMsgType.h"


// Kyle St.Amant
// 5/3/16
// GameLogger.h
// Simple logging for games.


class GameLogger
{
public: // public static methods
	static bool Initialize(const char* const path, const char* const filename);
	static bool Shutdown();

	template<typename...Args>
	static void Log(LogMsgType msgType, const char* const format, Args... args);
	//template<typename...Args>
	//static void CLog(LogMsgType msgType, const char* const format, Args... args);
private: // private static methods
	static void WriteLog(LogMsgType msgType, const char* const msg); // pre-pend time, error level, etc
	
	static std::ostream & ShowStats(std::ostream & os);
	static int msgTypeWidth;
private: // private static data
	static std::ofstream m_logStream;
	static int m_counts[int(LogMsgType::NumTypes)];


};




template<typename ...Args>
inline void GameLogger::Log(LogMsgType msgType, const char * const format, Args ...args)
{
	const int bufSize = 2048;
	char buffer[bufSize];
	sprintf_s(buffer, bufSize, format, args...);
	WriteLog(msgType, buffer);
}



//template<typename ...Args>
//inline void GameLogger::CLog(LogMsgType msgType, const char * const format, Args ...args)
//{
//	const int bufSize = 400;
//	char buffer[bufSize];
//	sprintf_s(buffer, bufSize, format, args...);
//	WriteCLog(msgType, buffer);
//}



#endif