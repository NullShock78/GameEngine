#include "TimeStamp.h"
#include <string.h>
#include <time.h>
#include <sys/timeb.h>

const char * TimeStamp::GetStamp(char * const buffer, int bufSize, bool colons)
{
	char format[30]{ 0 };
	if (colons)
	{
		strcat_s(format, 30, "%F %H:%M:%S:");
	}
	else
	{
		strcat_s(format, 30, "%F %H-%M-%S.");
	}

	
		const int millisize = 4;
		char milliBuf[millisize];
		struct _timeb timebuffer;

		_ftime64_s(&timebuffer);
		unsigned short millitime = timebuffer.millitm;
		sprintf_s(milliBuf, millisize, "%03d", millitime);


		time_t rawTime;
		time(&rawTime);
		struct tm timeInfo;
		localtime_s(&timeInfo, &rawTime);//Todo: check error val
		strftime(buffer, bufSize, format, &timeInfo);
		
	if (colons)
	{
		strcat_s(buffer, bufSize, milliBuf);
	}

	return buffer;
}

std::ostream & operator<<(std::ostream & os, TimeStamp & /*stamp*/)
{
	return os;
}