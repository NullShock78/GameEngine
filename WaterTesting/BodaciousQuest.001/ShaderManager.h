#ifndef  SHADER_MANAGER_H
#define SHADER_MANAGER_H

#pragma warning(push)  																											 
#pragma warning(disable:4201) 																								 
#include "GL\glew.h"	
#pragma warning(pop)

#include "ShaderProgram.h"
class ShaderManager
{
public:
	static bool Initialize();
	static bool Shutdown();
	static bool AddNewShader(const char * const vertexShader, const char * const fragmentShader);
	static GLuint GetShaderID(int shader);
	static bool UseShader(int shader);
	bool UseShaderFromID(GLuint shader);
	static ShaderProgram * GetShaderProgram(int shader);
private:
	static const int MAX_SHADERS = 20;
	static int m_numShaders;
	//static GLuint m_shaderIDs[MAX_SHADERS];
	static ShaderProgram m_shaderPrograms[MAX_SHADERS];
	static bool LinkShader(ShaderProgram shader);

};

#endif //def SHADER_MANAGER_H