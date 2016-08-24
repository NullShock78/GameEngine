#ifndef  CUBE_MANAGER_H
#define CUBE_MANAGER_H

//Kyle St.Amant
//7/7/2016
//Temporary: Manages cubes for lab 06
#include "GraphicalObject.h"
class ShaderProgram;

class CubeManager
{


private: 
	static const int NUM_CUBES{ 1000 };
	GraphicalObject m_cubes[NUM_CUBES];
	//GLsizei m_vertOffsets[5];
	//GLsizei m_indexOffsets[5];

	//GLuint		m_positionAttrib;
	//GLuint		m_colorAttrib;
	//GLenum		m_dataType;
	//GLboolean	m_isNormalized;
	//GLint		m_positionCount; //2D/3D																								 
	//GLint		m_colorCount;
	//GLint		m_stride;

	//GLuint m_vertexBufID;
	//GLuint m_indexBufID;

	ShaderProgram * m_shaderProgramPtr;
	GLint m_uniformLocCol;
	GLint m_uniformLocMat4;


	int bufContentSizeVertex;
	int bufContentSizeIndex;
	bool GetUniforms();
	bool FillBuffers();
	void InitializeCubes();
	//void InsertGLArraySubData(GLenum anchorTarget, GLsizei offset, GLsizei size, const void * data);
	//void CreateBuffer(GLuint * bufID, GLenum anchorTarget, GLsizei size, GLenum usage = GL_STATIC_DRAW);
	void InitCube(int index, glm::vec3 pos, glm::vec3 scale, glm::vec3 col, glm::vec3 rotationAxis);

public:
	bool Initialize(ShaderProgram * shaderProgram);
	bool Shutdown();

	void Update(float dt);
	void Draw(glm::mat4 perspective, glm::mat4 world_to_view);
	void AlignCube(int index, float degrees);
	void RotateCube(int index, float degrees, glm::vec3 axis);
	void RotateCubeRotAxis(int index, int dx, int dy);
};

#endif //def CUBE_MANAGER_H


