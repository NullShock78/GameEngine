#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

// Kyle St.Amant
// 6/26/2016
// ShaderProgram.h
// Wrapper class for an OpenGL Shader Program

#include <GL\glew.h>

const int maxShaderNameLen = 256;  // relative path to shader
const int maxShaders = 2;    // only need vertex and frag shaders for now

struct ShaderInfo
{
	bool   in_use = false;
	char   name[maxShaderNameLen]{ 0 }; // name[0] == '\0' if this shader info is empty
	GLuint id{ 0 };
	GLenum type{ 0 };      // shader type, eg, GL_VERTEX_SHADER
};

class ShaderProgram
{
public:
	bool Initialize();
	bool Shutdown();

	// Shader methods
	bool AddVertexShader(const char* const filename);
	bool AddFragmentShader(const char* const filename);
	bool AddShader(const char* const filename, GLenum shaderType); // prefer adding specific shaders
	bool CheckShaderCompileStatus(GLuint shaderID);

	// Program methods
	bool CheckProgramStatus(GLenum pname);
	bool CheckProgramStatus();
	bool LinkAndUseProgram();
	bool LinkProgram();
	bool UseProgram();
	GLint GetUniformLocation(const GLchar* name);
	GLint GetAttribLocation(const GLchar* name);

	GLint GetProgramId() const { return m_id; }

private:
	void ShowShaderLogInfo(GLuint shaderID, char* infoBuffer, GLint bufferLen);
	void ShowProgramLogInfo(char* infoBuffer, GLint bufferLen, GLenum pname);
	bool SaveShaderInfo(const char* const filename, GLenum shaderType, GLuint shaderId);
	bool DeleteShaders();
	bool DeleteProgram();

private:
	bool m_in_use;
	GLuint m_id;
	ShaderInfo m_shaders[maxShaders];
	//int m_current_shader;
};

#endif // ndef SHADERPROGRAM_H
