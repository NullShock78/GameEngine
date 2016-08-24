#ifndef BUFFER_INFO_H
#define BUFFER_INFO_H

#include "RenderInfo.h"
class GraphicalObject;
class Mesh;
class RenderInfo;
class BufferInfo
{

	
public:
	bool Initialize();
	bool AddMesh(Mesh * mesh, GLenum drawType, VertexFormats vertFormat);
	GraphicalObject * GetFirstGob();
	bool AddGraphicalObject(GraphicalObject * gob); //If doesn't match, return false
	bool Shutdown();
	bool GetHasData();
	bool SetBufferSize(int size);
	bool GobMatches(RenderInfo * renderInfo);

private:
	static int bufferInfoID;
	int m_id{ 0 };
	static const int DEFAULT_SIZE = 1000000;
	int m_vertexBufferSize;
	int m_indexBufferSize;

	int m_sizeOfVerts{ 0 };
	int m_sizeOfIndices{ 0 };
	GraphicalObject * m_firstObject;
	GraphicalObject * m_tailObj;
	RenderInfo * m_headRenderInfoPtr;
	RenderInfo * m_tailRenderInfoPtr;
	bool m_hasData{ false };
	GLuint m_vertBufferID{ 0 };
	GLuint m_indexBufferID{ 0 };

	bool m_isFull{ false };

	bool CreateBuffers();

	void GetCurrentOffsets(GLsizei * indexBytes, GLsizei * numVerts);
	void InsertVertexSubBuffer(GLuint bufferID, Mesh * mesh, GLsizei vertOffsetBytes);
	void InsertIndexSubBuffer(GLuint bufferID, Mesh * mesh, GLsizei indexOffsetBytes);
};

#endif // BUFFER_INFO_H