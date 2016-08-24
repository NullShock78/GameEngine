#include "BufferManager.h"
#include "GameLogger.h"

#include "RenderInfo.h"
#include "Mesh.h"
#include "GraphicalObject.h"

const int  BufferManager::NUM_IDS;
int  BufferManager::m_numBuffers;
GLuint  BufferManager::m_vertBufferIDs[NUM_IDS];
GLuint   BufferManager::m_indBufferIDs[NUM_IDS];
RenderInfo *  BufferManager::m_firstRenderInfoPtr;
GraphicalObject * BufferManager::m_firstObject;
GraphicalObject * BufferManager::m_tailObj;
RenderInfo * BufferManager::m_tailRenderInfo;
const int BufferManager::MAX_BUFFER_GROUPS;
BufferGroup BufferManager::m_bufferGroups[MAX_BUFFER_GROUPS];
int  BufferManager::m_numCurrentBufferGroups;
bool BufferManager::Initialize()
{
	m_numCurrentBufferGroups = 0;
	return m_bufferGroups[0].Initialize(0,VertexFormats::PositionOnly);

	
	/*m_numBuffers = 0;
	m_firstRenderInfoPtr = nullptr;

	CreateBuffers();

	GameLogger::Log(LogMsgType::cProcess, "BufferManager::Initialize() successful.");
	return true;*/
}

bool BufferManager::Shutdown()
{
	GameLogger::Log(LogMsgType::cProcess, "BufferManager::Shutdown() successful.");
	return m_bufferGroups[0].Shutdown();
}

bool BufferManager::AddMesh(Mesh * mesh, GLuint shaderID, GLenum drawType, VertexFormats vertFormat)
{
	//--------------------------------------------TEMP------------------------------------------------------------------------------------
	//--------------------------------------------TEMP------------------------------------------------------------------------------------
	//--------------------------------------------TEMP------------------------------------------------------------------------------------
	//--------------------------------------------TEMP------------------------------------------------------------------------------------
	//--------------------------------------------TEMP------------------------------------------------------------------------------------
	//--------------------------------------------TEMP------------------------------------------------------------------------------------
	//--------------------------------------------TEMP------------------------------------------------------------------------------------
		//return m_bufferGroups[0].AddMesh(mesh, drawType, vertFormat);
	//------------------------------------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------------------------------------
	//For later:
	int currentBufferGroup = 0;

	bool found = false;



	while (!found && currentBufferGroup < m_numCurrentBufferGroups) {

	found = m_bufferGroups[currentBufferGroup].MeshMatches(mesh, shaderID, vertFormat);

		if (!found) {
			++currentBufferGroup;
		}
		else
		{
			m_bufferGroups[currentBufferGroup].AddMesh(mesh,drawType,vertFormat);
			return true;
		}

	}

	if (!found)
	{
		if (m_numCurrentBufferGroups >= MAX_BUFFER_GROUPS)
		{
			GameLogger::Log(LogMsgType::cFatalError, " BufferManager::GetBufferGroup(): index out of bounds: MAX_GROUPS[%d] exceeded.", MAX_BUFFER_GROUPS);
			return false;
		}
		else
		{

			//++m_numCurrentBufferGroups;

			if (!m_bufferGroups[m_numCurrentBufferGroups].Initialize((int)shaderID, vertFormat)) {
				GameLogger::Log(LogMsgType::cFatalError, " BufferManager::GetBufferGroup(): BufferGroup[%d] failed to initialize.", m_numCurrentBufferGroups);
				return false;
			}
			//CreateBufferGroup(mesh->m_vertexType, shaderID);

			if(!m_bufferGroups[m_numCurrentBufferGroups].AddMesh(mesh,drawType,vertFormat)) return false;
			++m_numCurrentBufferGroups;

			return true;
		}

	}


	/*
	//TODO: Log



	//m_tailObj->SetNextObjectPtr(gob);
	//m_tailObj = gob;


	GLsizei indexSize = mesh->GetIndexSizeInBytes();
	GLsizei numIndices = mesh->GetNumIndices();
	GLsizei numVerts = mesh->GetNumVerts();
	GLsizei indexOffsetBytes = 0;
	GLsizei vertOffset = 0;
	GLsizei vertByteOffset = 0;

	//printf("\n\n\n\n\n\n\nAddMesh: INDEX SIZE ENUM Retrieved: %d\n\n\n\n\n\n", mesh->m_renderInfo.m_isb);

	if (m_firstRenderInfoPtr == nullptr)
	{
	m_firstRenderInfoPtr = mesh->GetRenderInfo();
	indexOffsetBytes = 0;
	vertOffset = 0;
	RenderInfo * meshRenderInfo = mesh->GetRenderInfo();
	meshRenderInfo->SetRenderInfo(m_vertBufferIDs[m_numBuffers-1],m_indBufferIDs[m_numBuffers - 1], indexSize,indexOffsetBytes,numIndices, numVerts, vertOffset);
	meshRenderInfo->SetIndexSizeEnum(mesh->GetIndexSizeEnum());
	//m_firstRenderInfoPtr = mesh->GetRenderInfo();
	m_tailRenderInfo = meshRenderInfo;

	}
	else
	{

	RenderInfo * meshRenderInfo = mesh->GetRenderInfo();
	GetCurrentOffsets(&indexOffsetBytes, &vertOffset);
	meshRenderInfo->SetRenderInfo(m_vertBufferIDs[m_numBuffers - 1], m_indBufferIDs[m_numBuffers - 1], indexSize, indexOffsetBytes, numIndices, numVerts, vertOffset);
	//meshRenderInfo->SetIndexSizeEnum(mesh->GetIndexSizeEnum());
	m_tailRenderInfo = meshRenderInfo;
	m_firstRenderInfoPtr->SetNextRenderInfoPtr(m_tailRenderInfo);
	}






	vertByteOffset = vertOffset * mesh->GetSingleVertexByteSize();


	InsertVertexSubBuffer(m_vertBufferIDs[0], mesh, vertByteOffset);
	InsertIndexSubBuffer(m_indBufferIDs[0], mesh, indexOffsetBytes);
	//InsertIndexSubBuffer
	//GLsizei indexSize, GLsizei indexOffsetBytes, GLsizei numIndices, GLsizei numVerts, bool enabled = true, RenderInfo * nextPtr = nullpt

	//Log stats
	GameLogger::Log(LogMsgType::cInfo, "--------BufferManager::AddMesh() Added mesh successfully-------");
	GameLogger::Log(LogMsgType::cInfo, "");
	GameLogger::Log(LogMsgType::cInfo, "--------------------| START BUFFER MESH INFO |---------------------");
	GameLogger::Log(LogMsgType::cInfo, "BufferManager::AddMesh(): NUM VERTS  [%u]", numVerts);
	GameLogger::Log(LogMsgType::cInfo, "BufferManager::AddMesh(): NUM INDICES[%u]", numIndices);
	GameLogger::Log(LogMsgType::cInfo, "--------------------|  END BUFFER MESH INFO  |---------------------");
	GameLogger::Log(LogMsgType::cInfo, "\n");
	return true;
	*/

	return true;
}

//bool BufferManager::AddMesh(Mesh * mesh)
//{
//	//TODO: Log
//	return m_bufferGroup.AddMesh(mesh);
//	
//
//	
//
//	//GLsizei indexSize = mesh->GetIndexSizeInBytes();
//	//GLsizei numIndices = mesh->GetNumIndices();
//	//GLsizei numVerts = mesh->GetNumVerts();
//	//GLsizei indexOffsetBytes = 0;
//	//GLsizei vertOffset = 0;
//	//GLsizei vertByteOffset = 0;
//	//if (m_firstRenderInfoPtr == nullptr)
//	//{
//	//	m_firstRenderInfoPtr = mesh->GetRenderInfo();
//	//	indexOffsetBytes = 0;
//	//	vertOffset = 0;
//	//	RenderInfo * meshRenderInfo = mesh->GetRenderInfo();
//	//	meshRenderInfo->SetRenderInfo(m_vertBufferIDs[m_numBuffers-1],m_indBufferIDs[m_numBuffers - 1], indexSize,indexOffsetBytes,numIndices, numVerts, vertOffset);
//	//	meshRenderInfo->SetIndexSizeEnum(mesh->GetIndexSizeEnum());
//	//	m_tailRenderInfo = meshRenderInfo;
//	//	
//	//}
//	//else
//	//{
//	//	
//	//	RenderInfo * meshRenderInfo = mesh->GetRenderInfo();
//	//	GetCurrentOffsets(&indexOffsetBytes, &vertOffset);
//	//	meshRenderInfo->SetRenderInfo(m_vertBufferIDs[m_numBuffers - 1], m_indBufferIDs[m_numBuffers - 1], indexSize, indexOffsetBytes, numIndices, numVerts, vertOffset);
//	//	m_tailRenderInfo = meshRenderInfo;
//	//	m_firstRenderInfoPtr->SetNextRenderInfoPtr(m_tailRenderInfo);
//	//}
//	//vertByteOffset = vertOffset * mesh->GetSingleVertexByteSize();
//	//InsertVertexSubBuffer(m_vertBufferIDs[0], mesh, vertByteOffset);
//	//InsertIndexSubBuffer(m_indBufferIDs[0], mesh, indexOffsetBytes);
//	////Log stats
//	//GameLogger::Log(LogMsgType::cInfo, "--------BufferManager::AddMesh() Added mesh successfully-------");
//	//GameLogger::Log(LogMsgType::cInfo, "");
//	//GameLogger::Log(LogMsgType::cInfo, "--------------------| START BUFFER MESH INFO |---------------------");
//	//GameLogger::Log(LogMsgType::cInfo, "BufferManager::AddMesh(): NUM VERTS  [%u]", numVerts);
//	//GameLogger::Log(LogMsgType::cInfo, "BufferManager::AddMesh(): NUM INDICES[%u]", numIndices);
//	//GameLogger::Log(LogMsgType::cInfo, "--------------------|  END BUFFER MESH INFO  |---------------------");
//	//GameLogger::Log(LogMsgType::cInfo, "\n");
//	//return true;
//}

bool BufferManager::AddGraphicalObject(GraphicalObject * gob)
{
	/*int curGroup = 0;
	while(curGroup < m_numBuffers)*/
	for (int j = 0; j < m_numCurrentBufferGroups; ++j)
	{
		if (m_bufferGroups[j].AddGraphicalObject(gob)) return true;
	}

		

	//return 


	//if (m_firstObject == nullptr) {
	//	m_firstObject = gob;
	//	m_tailObj = gob;
	//}
	//else
	//{
	//	m_tailObj->SetNextObjectPtr(gob);
	//	m_tailObj = gob;
	//}


	GameLogger::Log(LogMsgType::cFatalError, "BufferManager::AddGraphicalObject(): failed to add gob");
	
	
	return false;



}

GraphicalObject * BufferManager::GetFirstGob()
{
	return m_bufferGroups[0].GetFirstGob();
}

bool BufferManager::GetBufferGroup(BufferGroup *& bufferGroupToSet)
{
	static int curBufferGroup = 0;

	if (curBufferGroup < m_numCurrentBufferGroups)
	{
		bufferGroupToSet = &m_bufferGroups[curBufferGroup];
		++curBufferGroup;
		return true;
	}

	curBufferGroup = 0;

	return false;
}

void BufferManager::CreateBuffers()
{
	glGenBuffers(1, &m_vertBufferIDs[0]);
	glGenBuffers(1, &m_indBufferIDs[0]);
	//TODO: "For" loop here
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER,m_vertBufferIDs[0]);
	glBufferData(GL_ARRAY_BUFFER, 50000000, NULL, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indBufferIDs[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 50000000, NULL, GL_STATIC_DRAW);

	m_numBuffers = 1;//TODO: set ++ in array
}

void BufferManager::GetCurrentOffsets(GLsizei * indexBytes, GLsizei * numVerts)
{
	*indexBytes = m_firstRenderInfoPtr->CalculateIndexOffsetBytes();
	*numVerts = m_firstRenderInfoPtr->CalculateVertOffset();
}

void BufferManager::InsertVertexSubBuffer(GLuint bufferID, Mesh * mesh, GLsizei vertOffsetBytes)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glBufferSubData(GL_ARRAY_BUFFER, /*Vert byte offset*/vertOffsetBytes, mesh->GetVertSizeInBytes(), mesh->GetVertexDataStart());
	
}

void BufferManager::InsertIndexSubBuffer(GLuint bufferID, Mesh * mesh, GLsizei indexOffsetBytes)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, /*Vert byte offset*/indexOffsetBytes, mesh->GetIndexSizeInBytes(), mesh->GetIndexDataStart());

}
