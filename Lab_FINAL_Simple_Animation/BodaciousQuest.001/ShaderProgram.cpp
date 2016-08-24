#include "ShaderProgram.h"
#include "MyGL.h"
#include "GameLogger.h"
#include "MyFiles.h"
#include <string>
bool ShaderProgram::Initialize()
{
	GameLogger::Log(LogMsgType::Info, "Shader Init started");
	int glCreateResult = glCreateProgram();
	if (MyGL::TestForError(LogMsgType::cFatalError, "ShaderProgram::Initialize(): glCreateProgram() failed."))
	{
		return false;
	}
	GameLogger::Log(LogMsgType::Info, "Shader Program created.");
	//Test glCreateProgram() result.
	if (glCreateResult == 0)
	{
		GameLogger::Log(LogMsgType::cFatalError, "ShaderProgram::Initialize():glCreateProgram() returned 0");
		return false;
	}
	
	//GameLogger::Log(LogMsgType::Debug, "ShaderProgram::Initialize():glCreateProgram() return val = [%d]", glCreateResult);

	m_id = glCreateResult;
	m_in_use = true;
	GameLogger::Log(LogMsgType::Process, "ShaderProgram::Initialize()[%u] successful!",m_id);
	return true;
}

bool ShaderProgram::Shutdown()
{

	if (DeleteShaders())
	{
		if (!DeleteProgram())
		{
			GameLogger::Log(LogMsgType::cFatalError, "ShaderProgram[%u]::Shutdown() DeleteProgram() failure!", m_id);
			return false;
		}
	}
	else
	{
		GameLogger::Log(LogMsgType::cFatalError, "ShaderProgram[%u]::Shutdown() DeleteShaders() failure!", m_id);
		return false;
	}


	GameLogger::Log(LogMsgType::Process, "ShaderProgram[%u]::Shutdown successful!", m_id);
	return true;
}

bool ShaderProgram::AddVertexShader(const char * const filename)
{
	return AddShader(filename, GL_VERTEX_SHADER);
	//return true;
}

bool ShaderProgram::AddFragmentShader(const char * const filename)
{
	return AddShader(filename, GL_FRAGMENT_SHADER);
	//return true;
}

bool ShaderProgram::AddShader(const char * const filename, GLenum shaderType)
{
	//if (filename)

	GLuint shaderID = glCreateShader(shaderType);

	if (MyGL::TestForError(LogMsgType::cFatalError, "ShaderProgram::AddShader(): glCreateShader() failed."))
	{
		return false;
	}
	//GameLogger::Log(LogMsgType::Debug, " ShaderProgram::AddShader() glCreateShader ran successfully");

	if (shaderID == 0)
	{
		GameLogger::Log(LogMsgType::cFatalError, "glCreateShader() returned zero.");
		return false;
	}
	//GameLogger::Log(LogMsgType::Debug, " ShaderProgram::AddShader() valid shaderID created");


	//Read File
	GLchar * fileContents = MyFiles::ReadFileIntoString(filename);
	if (fileContents == nullptr) 
	{
		GameLogger::Log(LogMsgType::cFatalError, " ShaderProgram::AddShader() filecontents = nullptr");
		return false;
	}
	GameLogger::Log(LogMsgType::Debug, " ShaderProgram::AddShader() file with data was read in");


	//"Null-terminating file"
	const GLint size = -1;

	//glShaderSource
	glShaderSource(shaderID, 1, &fileContents, &size);
	if(MyGL::TestForError(LogMsgType::cFatalError, "ShaderProgram::AddShader(): glShaderSource():"))
	{
		return false;
	}
	GameLogger::Log(LogMsgType::Debug, "ShaderProgram::AddShader() : glShaderSource() successful");

	//glCompileShader
	glCompileShader(shaderID);
	if (MyGL::TestForError(LogMsgType::cFatalError, "ShaderProgram::AddShader(): glCompileShader() failed."))
	{
		delete[] fileContents;
		return false;
	}
	GameLogger::Log(LogMsgType::Debug, "ShaderProgram::AddShader() : glCompileShader() successful");
	delete[] fileContents;

	// CheckShaderCompileStatus
	if (!CheckShaderCompileStatus(shaderID))
	{
		GameLogger::Log(LogMsgType::cFatalError, "ShaderProgram::AddShader [%u] CheckShaderCompileStatus() bad.", shaderID);
		return false;
	}
	GameLogger::Log(LogMsgType::Debug, "ShaderProgram::AddShader() : glCompileShader() successful");

	if (!SaveShaderInfo(filename, shaderType, shaderID)) {
		//GameLogger::Log(LogMsgType::cError, "ShaderProgram::AddShader [%u] SaveShaderInfo() failed.", shaderID);
		return false;
	}

	//GameLogger::Log(LogMsgType::cDebug, "ShaderProgram::AddShader() : SaveShaderInfo() successful");

	//glAttachShader();
	glAttachShader(m_id, shaderID);
	if (MyGL::TestForError(LogMsgType::cFatalError, "ShaderProgram::AddShader(): Call to glAttachShader() failed."))
	{
		return false;
	}
	GameLogger::Log(LogMsgType::Debug, "ShaderProgram::AddShader() : glAttachShader() successful");

	GameLogger::Log(LogMsgType::Info, "ShaderProgram::AddShader [%u] successful.", shaderID);
	return true;
}

bool ShaderProgram::CheckShaderCompileStatus(GLuint shaderID)
{
	//TODO: ask for clarification
	
	GLint returnVal;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &returnVal);
	if (MyGL::TestForError(LogMsgType::cFatalError, " ShaderProgram::CheckShaderCompileStatus(): glGetShaderiv() Compile status bad."))
	{
		glDeleteShader(shaderID);
		return false;
	}

	
	if (returnVal != GL_TRUE) {
		
		GLint logLen;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLen);
		MyGL::TestForError(LogMsgType::cError, "ShaderProgram::CheckShaderCompileStatus(): glGetShaderiv(GL_INFO_LOG_LENGTH) failed.");
		GLchar * log = new GLchar[logLen]{ 0 };
		
		ShowShaderLogInfo(shaderID, log, logLen);
	
		delete[] log;
		return false;

	}
	
	GameLogger::Log(LogMsgType::Info, "ShaderProgram::CheckShaderCompileStatus(%u) successful.", shaderID);
	return true;
}

bool ShaderProgram::CheckProgramStatus(GLenum pname)
{
	GLint status;
	glGetProgramiv(m_id, pname, &status);
	//TODO add ... params
	if (MyGL::TestForError(LogMsgType::cFatalError, "ShaderProgram::CheckProgramStatus(): glGetProgramiv() failed"))
	{
		return false;
	}

	if (status == GL_FALSE) {
		GLint logLen;
		glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &logLen);
		if (MyGL::TestForError(LogMsgType::cError, "ShaderProgram::CheckProgramStatus(): glGetProgrmamiv(GL_INFO_LOG_LENGTH) failed."))
		{
			return false;
		}

		GLchar * log = new GLchar[logLen]{ 0 };

		ShowProgramLogInfo(log,logLen, pname);

		delete[] log;
		return false;
	}

	GameLogger::Log(LogMsgType::Info, "CheckProgramStatus() successful!" );//remember pname
	return true;
}

bool ShaderProgram::CheckProgramStatus()
{
	
	if (!CheckProgramStatus(GL_LINK_STATUS))
	{
		return false;
	}

	glValidateProgram(m_id);
	if (MyGL::TestForError(LogMsgType::cFatalError, "ShaderProgram::CheckProgramStatus(): glValidateProgram() failed."))
	{
		return false;
	}

	if (!CheckProgramStatus(GL_LINK_STATUS))
	{
		return false;
	}


	return true;
}

bool ShaderProgram::LinkAndUseProgram()
{
	glLinkProgram(m_id);
	if (MyGL::TestForError(LogMsgType::cFatalError, "ShaderProgram::LinkAndUseProgram(): glLinkProgram() failed."))
	{
		DeleteShaders();
		DeleteProgram();
		return false;
	}

	if (!CheckProgramStatus())
	{
		DeleteShaders();
		DeleteProgram();
		return false;
	}

	glUseProgram(m_id);
	if (MyGL::TestForError(LogMsgType::cFatalError, "ShaderProgram::LinkAndUseProgram(): glUseProgram() failed."))
	{
		
		DeleteShaders();
		DeleteProgram();
		return false;
	}

	GameLogger::Log(LogMsgType::Info, "Shader Program [%u] linked and used successfully.", m_id);
	return true;
}

bool ShaderProgram::LinkProgram()
{
	glLinkProgram(m_id);
	if (MyGL::TestForError(LogMsgType::cFatalError, "ShaderProgram::LinkProgram(): glLinkProgram() failed."))
	{
		DeleteShaders();
		DeleteProgram();
		return false;
	}

	if (!CheckProgramStatus())
	{
		DeleteShaders();
		DeleteProgram();
		return false;
	}
	return true;
}

bool ShaderProgram::UseProgram()
{
	//MyGL::TestForError(LogMsgType::ConsoleOnly, "errors accrued");
	glUseProgram(m_id);
	if (MyGL::TestForError(LogMsgType::cFatalError, "ShaderProgram::UseProgram(): glUseProgram() failed."))
	{
		DeleteShaders();
		DeleteProgram();
		return false;
	}
	return true;
}

GLint ShaderProgram::GetUniformLocation(const GLchar * name)
{
	GLint returnVal = glGetUniformLocation(m_id, name);
	if (MyGL::TestForError(LogMsgType::cError, "ShaderProgram::GetUniformLocation(): glGetUniformLocation() error"))
	{
		return GL_FALSE;
	}
	//GLint i = GL_INVALID_VALUE;
	//GLint j = GL_INVALID_OPERATION;
	if (returnVal == -1) {
		//j = GL_INVALID_OPERATION;
		return GL_FALSE;
	}

	GameLogger::Log(LogMsgType::Info, "GetUniformLocation [%s] successful.", name);
	return returnVal;
}

GLint ShaderProgram::GetAttribLocation(const GLchar * name)
{

	GLint returnVal = glGetAttribLocation(m_id, name);
	if (MyGL::TestForError(LogMsgType::cError, "ShaderProgram::GetAttribLocation(): glGetAttribLocation() error")) {
		GameLogger::Log(LogMsgType::cError, "Attempted to get attrib [%s]", name);
		return GL_FALSE;
	}
	if (returnVal == -1) {
		return GL_FALSE;
	}
	GameLogger::Log(LogMsgType::Info, "GetAttribLocation [%s] successful.", name);
	return returnVal;
}

void ShaderProgram::ShowShaderLogInfo(GLuint shaderID, char * infoBuffer, GLint bufferLen)
{
	//----------------------
	GLint returnLen;
	glGetShaderInfoLog(shaderID, bufferLen, &returnLen, infoBuffer);
	GameLogger::Log(LogMsgType::cInfo, "ShaderProgram::ShowShaderLogInfo(): glGetShaderInfoLog()\n\n %s", infoBuffer);
	if (MyGL::TestForError(LogMsgType::cFatalError, "---------\n Shader %u Compile errors: \n", shaderID))
	{
		GameLogger::Log(LogMsgType::Info, "\nAborting shader execution \n---------\n");
	}

}

void ShaderProgram::ShowProgramLogInfo(char * infoBuffer, GLint bufferLen, GLenum pname)
{
	GLint returnLen;
	
	glGetProgramInfoLog(m_id, bufferLen, &returnLen, infoBuffer);
	GameLogger::Log(LogMsgType::cInfo, "ShaderProgram::ShowProgramLogInfo(): glGetProgramInfoLog() for pName: [%u]\n\n %s", pname, infoBuffer);
	if (MyGL::TestForError(LogMsgType::cFatalError, "---------\n Program %u Compile errors: \n\n", m_id))
	{
		GameLogger::Log(LogMsgType::Info, "\nAborting Program execution \n---------\n");
	}
}

bool ShaderProgram::SaveShaderInfo(const char * const filename, GLenum shaderType, GLuint shaderId)
{
	bool searching = true;
	int current_index = 0;
	while (searching) {

		if (current_index > maxShaders)
		{
			GameLogger::Log(LogMsgType::cFatalError, "ShaderProgram::SaveShaderInfo() Shaders list m_shaders is full, max val:[%d]", maxShaders);
			return false;
		}
		else if (!m_shaders[current_index].in_use) {
			m_shaders[current_index].in_use = true;
			m_shaders[current_index].id = shaderId;
			strcat_s(m_shaders[current_index].name, maxShaderNameLen, filename);
			m_shaders[current_index].type = shaderType;
			searching = false;
		}
		else
		{
			++current_index;
		}
	}

	GameLogger::Log(LogMsgType::Info, "ShaderInfo saved successfully.");
	return true;
}

bool ShaderProgram::DeleteShaders()
{

	for (GLuint j = 0; j < maxShaders; ++j)
	{
		
		if (m_shaders[j].in_use) {
			GameLogger::Log(LogMsgType::Info, "Shader  [%d] deleting...", m_shaders[j].id);
			glDeleteShader(m_shaders[j].id);


			if (MyGL::TestForError(LogMsgType::cFatalError, "ShaderProgram::DeleteShaders(): glDeleteShader() failed, outputting val on next line."))
			{
				GameLogger::Log(LogMsgType::Info, "Shader  [%d] failed to delete.", m_shaders[j].id);
				return false;
			}
			//GameLogger::Log(LogMsgType::cInfo, "Shader [%d] deleted successfully", j);
			m_shaders[j].in_use = false;
			GameLogger::Log(LogMsgType::Info, "Shader  [%d] deleted successfully.", m_shaders[j].id);
		}
	}

	GameLogger::Log(LogMsgType::Info, "All shaders deleted successfully.");
	return true;
}

bool ShaderProgram::DeleteProgram()
{

	if (m_in_use)
	{
		glDeleteProgram(m_id);
		if(MyGL::TestForError(LogMsgType::cFatalError, "ShaderProgram::DeleteProgram(): glDeleteProgram() failed,  outputting val on next line.") )
		{
			GameLogger::Log(LogMsgType::cError, "Program [%u] failed to delete.", m_id);
			return false;
		}


		m_in_use = false;
	}

	GameLogger::Log(LogMsgType::cInfo, "Program [%u] deleted successfully.", m_id);
	return true;
}
