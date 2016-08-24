#ifndef  BUFFER_MANAGER_H
#define BUFFER_MANAGER_H

//Kyle St.Amant
//7/13/2016
//Manages Open GL buffers
#include "RenderInfo.h"
#include "BufferGroup.h"
class Mesh;
class GraphicalObject;
class BufferManager
{
private:

	static const int NUM_IDS{ 10 };

	//static GraphicalObject * m_lastAdded;

	static int		m_numBuffers;
	static GLuint	m_vertBufferIDs[NUM_IDS];
	static GLuint	m_indBufferIDs[NUM_IDS];

	//Ask about
	static GraphicalObject * m_firstObject;
	static GraphicalObject * m_tailObj;



	static RenderInfo * m_firstRenderInfoPtr;
	static RenderInfo * m_tailRenderInfo;
	//----------------
	//static GLsizei max_memory = 200000;
	static const int MAX_BUFFER_GROUPS = 20;
	static int m_numCurrentBufferGroups;
	static BufferGroup m_bufferGroups[MAX_BUFFER_GROUPS];

public:
	static bool Initialize();
	static bool Shutdown();
	static bool AddMesh(Mesh * mesh, GLuint shaderID, GLenum drawType,VertexFormats vertFormat);
	static bool AddGraphicalObject(GraphicalObject * gob);
	static GraphicalObject * GetFirstGob();
	static bool GetBufferGroup(BufferGroup *& bufferGroupToSet);
private: //Methods
	//void SetRenderInfo(Mesh * mesh);
	static void CreateBuffers();
	static void GetCurrentOffsets(GLsizei * indexBytes, GLsizei * numVerts);
	static void InsertVertexSubBuffer(GLuint bufferID, Mesh * mesh, GLsizei vertOffsetBytes);
	static void InsertIndexSubBuffer(GLuint bufferID, Mesh * mesh, GLsizei indexOffsetBytes);
};

#endif //def BUFFER_MANAGER_H


