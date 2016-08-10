#ifndef LOGMSGTYPE_H
#define LOGMSGTYPE_H
#include <ostream>

// Kyle St.Amant
// 5/5/16
// LogMsgType.h
// Enum type

enum class LogMsgType
{
	UnknownLogMsgType = 0,
	ConsoleOnly,
	Process,
	cProcess,
	Info,
	cInfo,
	Debug,
	cDebug,
	Warning,
	cWarning,
	Error,
	cError,
	FatalError,
	cFatalError,
	ProgrammerError,
	cProgrammerError,

	
	NumTypes // This one is always last
};

std::ostream& operator<<(std::ostream& os, LogMsgType msgType); 

bool ConsoleOut(LogMsgType t);// return true if output to console is indicated
#endif
