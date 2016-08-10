#ifndef MYGL_H_
#define MYGL_H_

// Robert Lamb
// 6/12/2016
// MyGL.h
// Utility class for OpenGL

#include <GL\glew.h>
#include "LogMsgType.h"

class MyGL
    {
    public:
        static const char* GetErrorMsg(GLenum errNum);
        static bool        TestForError(LogMsgType msgType, const char* msg);

        template<typename...Args>
        static bool TestForError (LogMsgType msgType, const char* const format, Args... args);

	private:
		static char * m_errorMessages[9];
    };

template<typename ...Args>
inline bool MyGL::TestForError (LogMsgType msgType, const char * const format, Args ...args)
    {
    const int bufSize = 400;
    char      buffer[bufSize];
    sprintf_s (buffer, bufSize, format, args...);
    return TestForError (msgType, buffer);
    }

#endif // ndef MYGL_H_