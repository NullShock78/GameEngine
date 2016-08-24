#include "MyGL.h"
#include "GameLogger.h"

char * MyGL::m_errorMessages[9] = {
	"GLInvalid Enum",
	"GLInvalid Value",
	"GLInvalid Operation",
	"GL Stack Overflow",
	"GL Stack Underflow, Deleted too much",
	"GL Out Of Memory",
	"GLInvalid Framebuffer Operation (framebuffer is not complete)",
	"GL Context lost (graphics card reset)",
	"GL Table too large"
};

const char * MyGL::GetErrorMsg(GLenum errNum)
{
	
	switch (errNum)
	{
	case GL_INVALID_ENUM:
		return m_errorMessages[0];	
	case GL_INVALID_VALUE:
		return m_errorMessages[1];
	case GL_INVALID_OPERATION:
		return m_errorMessages[2];	
	case GL_STACK_OVERFLOW:
		return m_errorMessages[3];	
	case GL_STACK_UNDERFLOW:
		return m_errorMessages[4];	
	case GL_OUT_OF_MEMORY:
		return m_errorMessages[5];
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		return m_errorMessages[6];	
	case GL_CONTEXT_LOST:
		return m_errorMessages[7];
	case GL_TABLE_TOO_LARGE:
		return m_errorMessages[8];	
	default:
		GameLogger::Log(LogMsgType::cError, "Unknown GL error! (%s)", errNum );
		return nullptr;
	}
	
}

bool MyGL::TestForError(LogMsgType msgType, const char * msg)
{
	
	GLenum tempGLEnum = glGetError();
	bool hasError = (tempGLEnum == GL_NO_ERROR)? false : true;
	while(tempGLEnum != GL_NO_ERROR)
	{
		GameLogger::Log(msgType, "%s\n GLErrorMsg:(%s).", msg, GetErrorMsg(tempGLEnum));
		tempGLEnum = glGetError();

	}

	//if(!hasError) GameLogger::Log(LogMsgType::cDebug, "TestForError call [%s] reporting that all is well.", msg);

	return hasError;
}
