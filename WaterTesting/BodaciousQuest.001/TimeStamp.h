#ifndef TIMESTAMP_H
#define TIMESTAMP_H

// Kyle St.Amant
// 5/3/16
// FilePath.h
// Utility

#include<ostream>

class TimeStamp
{
public:
	
	static const char * GetStamp(char * const buffer, int bufSize, bool colons = false);
	//std::ostream&
};

std::ostream& operator<<(std::ostream& os, TimeStamp & stamp);
#endif

