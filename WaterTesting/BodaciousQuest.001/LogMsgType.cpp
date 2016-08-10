#include "LogMsgType.h"

char * LogMsgWords[] =
{
	"Unknown",
	"ConsoleOnly",
	"Process",
	"cProcess",
	"Info",
	"cInfo",
	"Debug",
	"cDebug",
	"Warning",
	"cWarning",
	"Error",
	"cError",
	"FatalError",
	"cFatalError",
	"ProgError",
	"cProgError",
	"NumTypes"
};

//char * LogMsgCols[] =
//{
//	"orange",
//	"white",
//	"white",
//	"green",
//	"green",
//	"yellow",
//	"yellow",
//	"orange",
//	"orange",
//	"red",
//	"red",
//	"red",
//	"red",
//	"magenta",
//	"magenta",
//	"green"
//};
//
//LogColors logColors[] =
//{
//	orange,
//	white,
//	white,
//	green,
//	green,
//	yellow,
//	yellow,
//	orange,
//	orange,
//	red,
//	red,
//	red,
//	red,
//	magenta,
//	magenta,
//	green
//};

std::ostream & operator<<(std::ostream & os, LogMsgType msgType)
{
	return os << LogMsgWords[int(msgType)]; 
}

bool ConsoleOut(LogMsgType t)
{
	//Remove?
	if (t == LogMsgType::FatalError) return true;
	return (int(t) & 1);
}
