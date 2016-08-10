#include "BufferInfo.h"
#include "GameLogger.h"
#include "Mesh.h"
#include "GraphicalObject.h"


const int BufferInfo::DEFAULT_SIZE;
int BufferInfo::bufferInfoID = 0;

bool BufferInfo::Initialize()
{
	
	m_id = bufferInfoID;
		++bufferInfoID;
	

	//m_headRenderInfoPtr = nullptr;
	m_vertexBufferSize = DEFAULT_SIZE;
	m_indexBufferSize = DEFAULT_SIZE;
	

	GameLogger::Log(LogMsgType::cProcess, "BufferManager::Initialize() successful.");
	return true;
}

bool BufferInfo::AddMesh(Mesh * mesh, GLenum drawType,VertexFormats vertFormat)
{

	if (m_isFull) return false;

	//int id = m_id;

	if (mesh == nullptr)
	{
		printf("Mesh is nullptr\n");
		return false;
	}
	
	
	GLsizei totalIndexSizeBytes		= mesh->GetIndexSizeInBytes();
	GLsizei numIndices				= mesh->GetNumIndices();
	GLsizei numVerts				= mesh->GetNumVerts();

	GLsizei totalVertSizeBytes		= mesh->GetVertSizeInBytes();

	GLsizei indexOffsetBytes	= 0;
	GLsizei vertOffset			= 0;
	GLsizei vertByteOffset		= 0;
	RenderInfo * meshRenderInfo = mesh->GetRenderInfo();

	
	if (m_sizeOfVerts + totalVertSizeBytes > m_vertexBufferSize || m_sizeOfIndices + totalIndexSizeBytes > m_vertexBufferSize) {
		if (m_hasData)
		{
			m_isFull = true;
			return false;
		}
		else
		{
			totalVertSizeBytes  = m_vertexBufferSize = totalVertSizeBytes;
			totalIndexSizeBytes = m_indexBufferSize	 = totalIndexSizeBytes;
			m_isFull			= true;
		}
	}

	if (!m_hasData)
	{
		CreateBuffers();
	}

	//glBindBuffer(GL_ARRAY_BUFFER, m_vertBufferID);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);

	//printf("\n\n\n\n\n\n\nAddMesh: INDEX SIZE ENUM Retrieved: %d\n\n\n\n\n\n", mesh->m_renderInfo.m_isb);

	if (m_headRenderInfoPtr == nullptr)
	{
		m_headRenderInfoPtr = &mesh->m_renderInfo;
		indexOffsetBytes = 0;
		vertOffset = 0;

		meshRenderInfo->m_vertOffset = 0;
		meshRenderInfo->SetRenderInfo(m_vertBufferID, m_indexBufferID, totalIndexSizeBytes, indexOffsetBytes, numIndices, numVerts, vertOffset, true, nullptr, drawType, vertFormat);
		

		m_tailRenderInfoPtr = meshRenderInfo;

	}
	else
	{

		//meshRenderInfo = mesh->GetRenderInfo();

		GetCurrentOffsets(&indexOffsetBytes, &vertOffset);
		meshRenderInfo->m_vertOffset = vertOffset;
		meshRenderInfo->SetRenderInfo(m_vertBufferID, m_indexBufferID, totalIndexSizeBytes, indexOffsetBytes, numIndices, numVerts, vertOffset,true,nullptr, drawType,vertFormat);
		//meshRenderInfo->SetIndexSizeEnum(mesh->GetIndexSizeEnum());
		
		m_headRenderInfoPtr->SetNextRenderInfoPtr(m_tailRenderInfoPtr);
		m_tailRenderInfoPtr = meshRenderInfo;
	}

	//----------------------IMPORTANT?-----------------------------
	meshRenderInfo->SetIndexSizeEnum(mesh->GetIndexSizeEnum());
	//-------------------------------------------------------------
	meshRenderInfo->m_vertBufferID = m_vertBufferID;
	meshRenderInfo->m_indBufferID = m_indexBufferID;
	vertByteOffset = vertOffset * mesh->GetStride();
	
	if (mesh->m_renderInfo.m_stride == 0)mesh->m_renderInfo.m_stride = mesh->GetStride();
	//mesh->m_renderInfo.m_draw_mode = drawType;
	//mesh->m_renderInfo.m_vertexFormat = vertFormat;
	//mesh->m_renderInfo.m_vertexFormat =
	InsertVertexSubBuffer(m_vertBufferID, mesh, vertByteOffset);

	if (mesh->m_renderInfo.m_indexed) 
	{
		InsertIndexSubBuffer(m_indexBufferID, mesh, indexOffsetBytes);
	}

	//InsertIndexSubBuffer
	//GLsizei indexSize, GLsizei indexOffsetBytes, GLsizei numIndices, GLsizei numVerts, bool enabled = true, RenderInfo * nextPtr = nullpt

	//Log stats
	GameLogger::Log(LogMsgType::cInfo, "--------BufferInfo::AddMesh() Added mesh successfully-------");
	GameLogger::Log(LogMsgType::cInfo, "");
	GameLogger::Log(LogMsgType::cInfo, "--------------------| START BUFFER MESH INFO |-------------------------------------");
	GameLogger::Log(LogMsgType::cInfo, "BufferInfo::AddMesh(): NUM VERTS-----------------[%u]", numVerts);
	GameLogger::Log(LogMsgType::cInfo, "BufferInfo::AddMesh(): NUM INDICES---------------[%u]", numIndices);
	GameLogger::Log(LogMsgType::cInfo, "BufferInfo::AddMesh(): VERT OFFSET---------------[%u]", mesh->GetRenderInfo()->m_vertOffset);
	GameLogger::Log(LogMsgType::cInfo, "BufferInfo::AddMesh(): INDICES OFFSET (BYTES)----[%u]", mesh->GetRenderInfo()->m_indexOffsetBytes);
	GameLogger::Log(LogMsgType::cInfo, "--------------------|  END BUFFER MESH INFO  |--------------------------------------");
	GameLogger::Log(LogMsgType::cInfo, "\n");


	//void * t_buff = mesh->m_mesh;

	/*GLfloat * m_buffer = new GLfloat[500];
	glGetBufferSubData(GL_ARRAY_BUFFER, (GLintptr)0, 500, m_buffer);


	for (int j = 0; j < 500; j++)
	{

		printf("Val[%d]: %f\n",j ,*m_buffer);
		++m_buffer;
	}
	delete[] m_buffer;
*/
	

	m_hasData = true;
	return true;
}

GraphicalObject * BufferInfo::GetFirstGob()
{
	return m_firstObject;
}

bool BufferInfo::AddGraphicalObject(GraphicalObject * gob)
{

	RenderInfo * renderInfo =  gob->GetRenderInfoPtr();
	/*if (renderInfo != nullptr) {
		GLuint vID = renderInfo->m_vertBufferID;
	}*/

	if (renderInfo->m_vertBufferID != m_vertBufferID) {
		GameLogger::Log(LogMsgType::cInfo, "BufferInfo [%d] failed to add gob. Check if gob matches?", m_id);
		return false;
	}

	if (m_firstObject == nullptr) {
		m_firstObject = gob;
		m_tailObj = gob;
	}
	else
	{
		if (m_tailObj == gob)
		{
			GameLogger::Log(LogMsgType::cError, "BufferInfo [%d] gob tail is the same", m_id);
			return false;
		}
		m_tailObj->SetNextObjectPtr(gob);
		m_tailObj = gob;
	}


	return true;
}

bool BufferInfo::Shutdown()
{


	return true;
}

bool BufferInfo::GetHasData()
{
	return m_hasData;
}

bool BufferInfo::SetBufferSize(int size)
{
	m_vertexBufferSize = size;
	return true;
}

bool BufferInfo::GobMatches(RenderInfo * renderInfo)
{
	return(renderInfo->m_vertBufferID == m_vertBufferID);


	//return false;
}


bool BufferInfo::CreateBuffers()
{
	
	glGenBuffers(1, &m_vertBufferID);
	glGenBuffers(1, &m_indexBufferID);
	//TODO: add to render engine
	glEnableVertexAttribArray(0);//move to render engine
	glEnableVertexAttribArray(1);//move to render engine
								
	glBindBuffer(GL_ARRAY_BUFFER, m_vertBufferID);
	glBufferData(GL_ARRAY_BUFFER, m_vertexBufferSize, NULL, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_vertexBufferSize, NULL, GL_STATIC_DRAW);

	GameLogger::Log(LogMsgType::cInfo, "\n-----------------------------------------------------------------------\n BufferInfo::CreateBuffers()[%d] Created buffers:| VERTEX [%u] with [%d] bytes. || INDEX [%u] with [%d] bytes |\n-----------------------------------------------------------------------\n",m_id, m_vertBufferID, m_vertexBufferSize, m_indexBufferID, m_indexBufferSize);

	return true;
}

void BufferInfo::GetCurrentOffsets(GLsizei * indexBytes, GLsizei * numVerts)
{
	*indexBytes = m_headRenderInfoPtr->CalculateIndexOffsetBytes();
	*numVerts = m_headRenderInfoPtr->CalculateVertOffset();
}

void BufferInfo::InsertVertexSubBuffer(GLuint /*bufferID*/, Mesh * mesh, GLsizei vertOffsetBytes)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertBufferID);
	//GLsizei vSize = mesh->GetVertSizeInBytes();
	//GLfloat * temp = reinterpret_cast<GLfloat*>(mesh->GetVertexDataStart());


	//float * temp = reinterpret_cast<float *>( mesh->GetVertexDataStart());

	//GLsizei a = mesh->GetNumVerts();
	//GLsizei b = mesh->GetVertSizeInBytes();

	/*for (int j = 0; j < b; j++)
	{

		printf("Val[%d]: %f\n", j, *temp);
		++temp;
	}*/
	glBufferSubData(GL_ARRAY_BUFFER, /*Vert byte offset*/vertOffsetBytes, mesh->GetVertSizeInBytes(), (void*)mesh->GetVertexDataStart());
	
	//GLfloat * m_buffer = new GLfloat[100];
	//glGetBufferSubData(GL_ARRAY_BUFFER, (GLintptr)0, 100, m_buffer);


	//for (int j = 0; j < 100; j++)
	//{

	//	printf("Val[%d]: %f\n", j, m_buffer[j]);
	//	//++m_buffer;
	//}
	//delete[] m_buffer;

	//int i = 0;
	//i++;

	//GLfloat * m_buffer = new GLfloat[100];
	//glGetBufferSubData(GL_ARRAY_BUFFER, (GLintptr)0, 100, m_buffer);


	//for (int j = 0; j < 100; j++)
	//{

	//	printf("Val[%d]: %f\n", j, m_buffer[j]);
	//	//++m_buffer;
	//}
	//delete[] m_buffer;

	//int i = 0;
	//i++;
}

void BufferInfo::InsertIndexSubBuffer(GLuint /*bufferID*/, Mesh * mesh, GLsizei indexOffsetBytes)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, /*Vert byte offset*/indexOffsetBytes, mesh->GetIndexSizeInBytes(), mesh->GetIndexDataStart());

}
