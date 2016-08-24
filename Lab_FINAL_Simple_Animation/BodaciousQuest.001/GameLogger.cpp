#include "GameLogger.h"
#include <iostream>
#include <ctime>
#include <iomanip>
#include<string.h>
#include"FilePath.h"
#include "TimeStamp.h"

std::ofstream GameLogger::m_logStream;
int	GameLogger::m_counts[int(LogMsgType::NumTypes)];
int GameLogger::msgTypeWidth;
bool GameLogger::Initialize(const char * const path, const char * const filename)
{
	time_t timeNow = time(0);
	struct tm now;
	localtime_s(&now, &timeNow);

	const int bufferLen = 200;
	char buffer[bufferLen]{ 0 };

	const int stampSize = 80;
	char stamp[stampSize];

	TimeStamp::GetStamp(stamp, stampSize);
	FilePath::Create(buffer, bufferLen, path, stamp, filename);

	m_logStream.open(buffer, std::ios::trunc);

	if (!m_logStream)
	{
		std::cerr << "FATAL ERROR: GameLogger::Initialize() failed to open " << buffer << " for writing!\n";
		return false;
	}
	msgTypeWidth = 13; //TODO: do something about this, config reader is not an option!

	//m_logStream << "<!DOCTYPE html>\n<html>\n<head>\n<title>Log</ title></head>\n<body>" << std::endl;
	//TODO: success log here
	Log(LogMsgType::Process, "GameLogger::Initialize() opened log file [%s] for writing", buffer);
	Log(LogMsgType::Info, "GameLogger::Initialize() successful");
	return true;
}

std::ostream & GameLogger::ShowStats(std::ostream & os) {
	os << "Begin Log Message Count by Type\n";
	for (int j = 0; j < int(LogMsgType::NumTypes); j++)
	{
		if (m_counts[j] > 0) {
			os << std::left << "   [" << std::setw(msgTypeWidth) << LogMsgType(j) << "]  = " << m_counts[j] << "\n";
		}
	}
	os << "End Log Message Count by Type\n";
	return os;
}

bool GameLogger::Shutdown()
{
	Log(LogMsgType::Process, "GameLogger::ShutDown() successful");
	ShowStats(std::cout);
	m_logStream.close();
	return true; //TODO: change
}


//void GameLogger::WriteCLog(LogMsgType msgType, const char * const msg)
//{
//	if (m_logStream) {
//
//
//
//		time_t timeNow = time(0);
//		struct tm now;
//		localtime_s(&now, &timeNow);
//
//		const int buffSize = 80;
//		char * timeBuffer = new char[buffSize] { 0 };
//
//		TimeStamp::GetStamp(timeBuffer, buffSize, true);
//
//		++m_counts[int(msgType)];
//
//		m_logStream << timeBuffer << "[" << std::left << std::setw(10) << msgType << "] " << msg << std::endl;
//		std::cout << timeBuffer << "[" << std::left << std::setw(10) << msgType << "] " << msg << std::endl;
//	}
//	else
//	{
//		std::cout << "ERROR: Log file not writeable!\n";
//	}
//}

void GameLogger::WriteLog(LogMsgType msgType, const char * const msg)
{
	if (m_logStream) {

		time_t timeNow = time(0);
		struct tm now;
		localtime_s(&now, &timeNow);

		const int buffSize = 80;
		char * timeBuffer = new char[buffSize] { 0 };

		TimeStamp::GetStamp(timeBuffer, buffSize, true);

		++m_counts[int(msgType)];

		if (int(msgType) != 1) {
			m_logStream << timeBuffer << "[" << std::left << std::setw(msgTypeWidth) << msgType << "] " << msg << std::endl;
		}

		if (ConsoleOut(msgType)) {
			std::cout << "[" << std::left << std::setw(msgTypeWidth) << msgType << "] " << msg << std::endl;
		}


	}
	else
	{
		std::cerr << "ERROR: Log file not writeable!\n";
	}
}

