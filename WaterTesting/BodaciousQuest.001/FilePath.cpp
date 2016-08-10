#include "FilePath.h"
#include<string.h>
#include<assert.h>
//Return ptr to end of buffer
char * CopyString(char * const buffer, int bufSize,
	const char * const str)
{
	if (str == nullptr) return buffer;
	if (*str == 0)		return buffer;
	int len = strlen(str);
	assert(bufSize > len);
	strcpy_s(buffer, bufSize, str);
	return buffer + len;
}

char * CopyPath(char * const buffer, int bufSize,
	const char * const str)
{
	char * p = CopyString(buffer, bufSize, str);

	if (p == buffer) return p;
	
	if (*(p-1) != '\\')
	{
		*p = '\\'; //Check for room?
		++p;
	}
	return p;

}
char * FilePath::Create(char * const buffer, int bufSize, 
						const char * const path, 
						const char * const stamp, 
						const char * const filename)
{
	char*p = buffer;
	p = CopyPath	(p, bufSize-1, path); //Leave room for path
	p = CopyString	(p, bufSize - (p-buffer), stamp);
	p = CopyString(p, bufSize - (p - buffer), filename);
	return nullptr;
}
