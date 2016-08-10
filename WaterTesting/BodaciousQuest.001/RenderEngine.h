#ifndef  RENDER_ENGINE_H
#define RENDER_ENGINE_H

//Kyle St.Amant
//7/13/2016
//description here
#pragma warning(push)  //Save state
#pragma warning(disable:4127) //disable warning
#pragma warning(disable:4251)
#pragma warning(disable:4100)
#pragma warning(disable:4201)
#include "GL\glew.h"
#include "mat4x4.hpp"
//#include "Buff"

#pragma warning(pop) 
#include "RenderInfo.h"
#include "VertexFormats.h"
class Mesh;
class GraphicalObject;
class ShaderProgram;
class BufferGroup;
class RenderEngine
{
private:
	//static GraphicalObject * m_firstObject;

	static GLuint m_colorAttrib;
	static GLuint m_positionAttrib;

	static GLuint m_uniformLocCol;
	static GLuint m_uniformLocMat4;
	static ShaderProgram * m_shaderProgramPtr;

	static bool SetUniformsShader0(GraphicalObject * gob, glm::mat4 screenMat);
	static bool SetUniformsShader1(GraphicalObject * gob, glm::mat4 screenMat);
	static bool SetUniformsShader2(GraphicalObject * gob, glm::mat4 screenMat);
	static bool SetUniformsShader4(GraphicalObject * gob, glm::mat4 screenMat);
	static bool SetUniformsShader5(GraphicalObject * gob, glm::mat4 screenMat);
public:
	static bool Initialize(ShaderProgram * shaderP);
	static bool Shutdown();
	static bool GetUniforms();
	static bool AddMesh(Mesh * mesh, GLuint shaderID = 0, GLenum drawType = GL_TRIANGLES, VertexFormats vertFormat = VertexFormats::PositionColor);
	static bool AddGraphicalObject(GraphicalObject * gob);
	static bool Draw(glm::mat4 perspective, glm::mat4 camera);
	static void DrawIndexedObject(GraphicalObject * gob);
	static void DrawNonIndexedObject(GraphicalObject * gob);
	static bool SetAttributes( VertexFormats * vertType, GLsizei stride);
	//static bool SetAttributes(BufferGroup * bGroup);
	static void SetAttrib(GLuint & attribIndex, GLint quantity, GLsizei vertexStride, GLsizei currentOffset, GLsizei & formatOffset);
	static GLenum GetIndexType(IndexSizeInBytesEnum indexSize);
	static bool AttachLight(GraphicalObject * gob, GraphicalObject * lightGob);
};

#endif //def RENDER_ENGINE_H


