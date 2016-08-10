#ifndef BUFFER_GROUP_H
#define BUFFER_GROUP_H
#include "BufferInfo.h"

class Mesh;
class GraphicalObject;
class BufferGroup
{
public:
	bool Initialize(int shaderIndex, VertexFormats vertFormat);
	bool AddMesh(Mesh * mesh, GLenum drawType, VertexFormats vertFormat);
	bool AddGraphicalObject(GraphicalObject * gob);
	bool Shutdown();
	bool MeshMatches(Mesh * m, GLuint shaderID, VertexFormats vertFormat);
	bool GetBufferInfoGob(GraphicalObject *& gob);
	int GetShaderIndex();
	GraphicalObject * GetFirstGob();
	VertexFormats * GetVertexFormat();
	GLsizei GetStride();
private:
	static int currentGroupID;
	GraphicalObject * m_headGob;
	GraphicalObject * m_tailGob;
	static const int MAX_BUFFERS = 50;
	BufferInfo m_bufferInfo[MAX_BUFFERS];
	VertexFormats m_format;
	GLuint m_shaderID{ 0 };
	GLuint m_shaderIndex;
	int m_id{ -1 };
	int m_numOfBufferInfos{ 0 };
};

#endif //BUFFER_GROUP_H
