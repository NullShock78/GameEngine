#include "RenderInfo.h"



void RenderInfo::SetRenderInfo(GLuint vertBufferID, GLuint indBufferID, GLsizei indexSize, GLsizei indexOffsetBytes, GLsizei numIndices, GLsizei numVerts, GLsizei vertOffset, bool enabled, RenderInfo * nextPtr, GLenum drawMode, VertexFormats format, IndexSizeInBytesEnum indexSizeBytesEnum)
{
	m_vertBufferID = vertBufferID;
	m_indBufferID = indBufferID;
	SetIndexBytes(indexSize);
	SetIndexOffsetBytes(indexOffsetBytes);
	SetNumOfIndices(numIndices);
	SetNumOfVerts(numVerts);
	SetVertOffset(vertOffset);
	m_enabled = enabled;

	m_next = nextPtr;
	//SetNextRenderInfoPtr(nextPtr);
	m_draw_mode = drawMode;
	m_vertexFormat = format;
	m_isb = indexSizeBytesEnum;

}

void RenderInfo::SetIndexSizeEnum(IndexSizeInBytesEnum isb)
{
	m_isb = isb;
}

//void RenderInfo::SetRenderInfo(RenderInfo toCopy)
//{
//	m_enabled = toCopy.m_enabled;
//	m_indexSizeBytes = toCopy.m_indexSizeBytes;
//	m_numIndices = toCopy.m_numIndices;
//	m_numVerts = toCopy.m_numVerts;
//	m_shader = toCopy.m_shader;
//}
//void RenderInfo::SetIndexOffsetBytesEnum(IndexSizeInBytes sib) {
//	m_indexSizeBytes
//}


void RenderInfo::SetIndexOffsetBytes(GLsizei indexOffsetBytes)
{
	m_indexOffsetBytes = indexOffsetBytes;
}

void RenderInfo::SetIndexBytes(GLsizei indexSize)
{
	m_indexSizeBytes = indexSize;
}

void RenderInfo::SetNumOfIndices(GLsizei numIndices)
{
	m_numIndices = numIndices;
}

void RenderInfo::SetNumOfVerts(GLsizei numVerts)
{
	m_numVerts = numVerts;
}

void RenderInfo::SetVertOffset(GLsizei vertOffset)
{
	m_vertOffset = vertOffset;
}

void RenderInfo::SetNextRenderInfoPtr(RenderInfo * info)
{
	if (m_next == nullptr)
	{
		m_next = info;
	}
	else
	{
		m_next->SetNextRenderInfoPtr(info);
	}
}

//GLsizei RenderInfo::GetVertOffset()
//{
//	if (m_next != nullptr && m_next->m_next != nullptr)
//	{
//		return m_numVerts + m_next->GetVertOffset();
//	}
//	else
//	{
//		return m_numVerts;
//	}
//
//}

int RenderInfo::CalculateIndexOffsetBytes()
{

	if (m_next != nullptr)
	{
		return m_indexSizeBytes + m_next->CalculateIndexOffsetBytes();
	}
	else
	{
		return m_indexSizeBytes;
	}
	
}

int RenderInfo::CalculateVertOffset()
{
	//---------------------|Will never be called if this.m_next is nullptr
	if (m_next != nullptr)
	{
		return m_numVerts + m_next->CalculateVertOffset();
	}
	else
	{
		return m_numVerts;
	}
}
