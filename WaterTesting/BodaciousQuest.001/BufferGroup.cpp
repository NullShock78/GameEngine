#include "BufferGroup.h"
#include "Mesh.h"
#include "ShaderManager.h"
int BufferGroup::currentGroupID = 0;

bool BufferGroup::Initialize(int shaderIndex, VertexFormats vertFormat)
{
	m_id = currentGroupID;
	++currentGroupID;

	m_shaderIndex = shaderIndex;
	m_format = vertFormat;
	m_shaderID = ShaderManager::GetShaderID(shaderIndex);

	return m_bufferInfo[0].Initialize();
}

bool BufferGroup::AddMesh(Mesh * mesh, GLenum drawType, VertexFormats vertFormat)
{

	 
	//if not enough room

	bool done = false;
	while (!done) {

		if (m_numOfBufferInfos >= MAX_BUFFERS) 
		{
			GameLogger::Log(LogMsgType::cFatalError, "BufferGroup::AddMesh(): m_numOfBufferInfos[%d] exceeds MAX_BUFFERS[%d]", m_numOfBufferInfos, MAX_BUFFERS);
			return false;
		}

		if (!m_bufferInfo[m_numOfBufferInfos].AddMesh(mesh, drawType, vertFormat)) 
		{
			//if new
			//if (!m_bufferInfo[m_numOfBufferInfos].GetHasData())
			//{
			//	m_bufferInfo[m_numOfBufferInfos].SetBufferSize(mesh->GetIndexSizeInBytes());
			//	return m_bufferInfo[m_numOfBufferInfos].AddMesh(mesh, drawType, vertFormat);
			//}
			//else
			//{
				++m_numOfBufferInfos;
				m_bufferInfo[m_numOfBufferInfos].Initialize();
			//}
		}
		else
		{
			done = true;
		}
	}


	return true;
}

bool BufferGroup::AddGraphicalObject(GraphicalObject * gob)
{

	//TODO:
	//MAKE SURE THAT the gob goes to the right bufferInfo

	//bool retval = m_bufferInfo[0].AddGraphicalObject(gob);
	//return retval;


	for (int j = 0; j <= m_numOfBufferInfos; ++j)
	{
		if (m_bufferInfo[j].AddGraphicalObject(gob)) { return true; }
	}

	//GameLogger::Log(LogMsgType::cProgrammerError, "BufferGroup::AddGraphicalObject(): BufferGroupID[%d]: Unable to add gob, check code.", m_id);
	//Check next
	return false;
}

bool BufferGroup::Shutdown()
{

	return true;
}

bool BufferGroup::MeshMatches(Mesh * /*m*/, GLuint shaderID, VertexFormats vertFormat)
{
	//TODO: compare shaderIDs
	if (shaderID == m_shaderIndex && vertFormat == m_format) {
		



		/*	
		if (m->m_vertexType == m_vertexType)
		{
			return true;
		}
		*/

		return true;

	}
	return false;
}

bool BufferGroup::GetBufferInfoGob(GraphicalObject *& gob)
{
	static int curGob = 0;

	if (curGob <= m_numOfBufferInfos)
	{
		gob = m_bufferInfo[curGob].GetFirstGob();
		++curGob;
		return true;
	}
	else
	{
		curGob = 0;
		return false;
	}
}

int BufferGroup::GetShaderIndex()
{
	return m_shaderIndex;
}


GraphicalObject * BufferGroup::GetFirstGob()
{
	return m_bufferInfo[0].GetFirstGob();
}

VertexFormats * BufferGroup::GetVertexFormat()
{
	return &m_format;
}

GLsizei BufferGroup::GetStride()
{
	//TODO: make dynamic
	return 0;
}
