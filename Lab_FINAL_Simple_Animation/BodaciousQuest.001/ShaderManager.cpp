#include "ShaderManager.h"

#include "ShaderManager.h"

#include "GameLogger.h"
#include "MyGL.h"

const int ShaderManager::MAX_SHADERS;
int ShaderManager::m_numShaders;
//GLuint ShaderManager::m_shaderIDs[MAX_SHADERS];
ShaderProgram ShaderManager::m_shaderPrograms[MAX_SHADERS];


bool ShaderManager::Initialize()
{
	m_numShaders = 0;
	GameLogger::Log(LogMsgType::Process, "ShaderManager Initialized successfully");
	return true;
}

bool ShaderManager::Shutdown()
{
	bool retval = true;
	for (int j = 0; j < m_numShaders; j++)
	{
		printf("\nm_shaderProgram[%d] shutting down.\n\n", m_shaderPrograms[j].GetProgramId());
		if (!m_shaderPrograms[j].Shutdown()) retval = false;
	}
	return retval;
}

bool ShaderManager::AddNewShader(const char * const vertexShader, const char * const fragmentShader)
{

	//TODO: Replace 0 with number

	//glViewport(0, 0, m_window->width(), m_window->height());
	/*if (!m_shaderPrograms[m_currentShader].Initialize()) {
	GameLogger::Log(LogMsgType::cError, "ShaderManager::AddNewShader()[%d]:m_program.Initialize() failed.",m_currentShader);
	return false;
	}
	if (!m_shaderPrograms[m_currentShader].AddVertexShader(vertexShader)) {
	GameLogger::Log(LogMsgType::cError, "ShaderManager::AddNewShader()[%d]:AddVertexShader failed.", m_currentShader);
	return false;
	}
	if (!m_shaderPrograms[m_currentShader].AddFragmentShader(fragmentShader)) {
	GameLogger::Log(LogMsgType::cError, "ShaderManager::AddNewShader()[%d]:AddFragShader failed. ", m_currentShader);
	return false;
	}*/

	if (!m_shaderPrograms[m_numShaders].Initialize()) {
		GameLogger::Log(LogMsgType::cError, "ShaderManager::AddNewShader()[%d]:m_program.Initialize() failed.", m_numShaders);
		return false;
	}

	//printf("SH")

	if (!m_shaderPrograms[m_numShaders].AddVertexShader(vertexShader)) {
		GameLogger::Log(LogMsgType::cError, "ShaderManager::AddNewShader()[%s]:AddVertexShader failed.", vertexShader);
		return false;
	}
	if (!m_shaderPrograms[m_numShaders].AddFragmentShader(fragmentShader)) {
		GameLogger::Log(LogMsgType::cError, "ShaderManager::AddNewShader()[%s]:AddFragShader failed. ", fragmentShader);
		return false;
	}
	bool retVal = (m_shaderPrograms[m_numShaders].LinkProgram());

	if(retVal) ++m_numShaders;
	
	return retVal;
}

GLuint ShaderManager::GetShaderID(int shader)
{

	if (shader >= m_numShaders) return 0;
	//MyGL::TestForError(LogMsgType::cDebug, "ERRORS before GetProgramId...");
	return m_shaderPrograms[shader].GetProgramId();
	//MyGL::TestForError(LogMsgType::cDebug, "ERRORS after GetProgramId...");

}

bool ShaderManager::UseShader(int shader)
{
	if (shader >= m_numShaders || shader < 0) {
		GameLogger::Log(LogMsgType::cFatalError, "ShaderManager::UseShader() index out of bounds,. passed in [%d], currentShader is: [%d]", shader, m_numShaders);
		return false;
	}
	if (GetShaderID(shader) == 0)
	{
		GameLogger::Log(LogMsgType::cFatalError, "ShaderManager::UseShader() shader[%d]'s ID is 0", shader);
		return false;
	}
	 bool retVal = m_shaderPrograms[shader].UseProgram();
	 if (!retVal) {
		 GameLogger::Log(LogMsgType::cProgrammerError, "ShaderManager::UseShader() failed");
	 }


	 return retVal;

}

bool ShaderManager::UseShaderFromID(GLuint shader)
{
	if ((int)shader >= m_numShaders || shader < 0) {
		GameLogger::Log(LogMsgType::cFatalError, "ShaderManager::UseShader() index out of bounds. passed in [%d], currentShader is: [%d]", shader, m_numShaders);
		return false;
	}
	return m_shaderPrograms[shader].UseProgram();
}


ShaderProgram * ShaderManager::GetShaderProgram(int shader)
{
	if (shader >= m_numShaders || shader < 0) {
		GameLogger::Log(LogMsgType::cFatalError, "ShaderManager::GetShaderProgram() index out of bounds. passed in [%d], currentShader is: [%d]", shader, m_numShaders);
		return false;
	}
	return &m_shaderPrograms[shader];
}

bool ShaderManager::LinkShader(ShaderProgram shader)
{
	return shader.LinkProgram();
}