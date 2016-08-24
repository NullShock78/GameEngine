#ifndef FILE_PATH_H
#define FILE_PATH_H

// Kyle St.Amant
// 5/3/16
// FilePath.h
// Utility Class
class FilePath
{
public:
	static char * Create(char* const buffer, int bufSize,
		const char * const path,
		const char * const stamp,
		const char * const filename);
};


#endif

