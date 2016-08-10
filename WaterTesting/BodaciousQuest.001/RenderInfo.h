#ifndef  RENDER_INFO_H
#define RENDER_INFO_H

//Kyle St.Amant
//7/13/2016
//description here

#pragma warning(push)  //Save state
#pragma warning(disable:4127) //disable warning
#pragma warning(disable:4251)
#pragma warning(disable:4100)
#include "GL\glew.h"

#pragma warning(pop) 

#include "IndexSizeInBytesEnum.h"
#include "ModelSize.h"
#include "VertexFormats.h"
//Pretty much a struct
class RenderInfo
{

	/*RenderInfo() {};

	RenderInfo(bool enabled, GLsizei indexSize, GLsizei numIndices, GLsizei numVerts, GLuint shader)
		:
		m_enabled(enabled),

		m_indexSizeBytes(indexSize),
		m_numIndices(numIndices),
		m_numVerts(numVerts),
		m_shader(shader)
	{

	}
	~RenderInfo() {};*/
public:
	RenderInfo * m_next{ nullptr };

	bool m_enabled{ false };
	GLsizei m_indexSizeBytes;
	GLsizei m_indexOffsetBytes;
	GLsizei m_numIndices;
	//Do I need?
	GLsizei m_numVerts;
	//------------
	GLsizei m_vertOffset;
	GLuint m_shader{ 0 };
	GLuint m_vertBufferID;
	GLuint m_indBufferID;
	IndexSizeInBytesEnum m_isb{ IndexSizeInBytesEnum::Uint };
	// Not used?
	GLenum m_draw_mode{ GL_TRIANGLES };
	int m_wroteShader{ 2 };
	VertexFormats m_vertexFormat{ VertexFormats::PositionColor };
	//int  m_type;
	bool m_indexed{ true };
	GLsizei m_stride;
	//GLsizei m_singleVertSize;
public:
	void SetRenderInfo(GLuint vertBufferID, GLuint indBufferID, GLsizei indexSize, GLsizei indexOffsetBytes, GLsizei numIndices, GLsizei numVerts, GLsizei vertOffset, bool enabled = true, RenderInfo * nextPtr = nullptr, GLenum drawMode = GL_TRIANGLES,VertexFormats format = VertexFormats::PositionColor, IndexSizeInBytesEnum indexSizeBytesEnum = IndexSizeInBytesEnum::Uint);

	void SetIndexSizeEnum(IndexSizeInBytesEnum isb);

	//void SetRenderInfo(RenderInfo toCopy);
	void SetIndexOffsetBytes(GLsizei indexSize);
	void SetIndexBytes(GLsizei indexSize);
	void SetNumOfIndices(GLsizei numIndices);
	void SetNumOfVerts(GLsizei numVerts);
	void SetVertOffset(GLsizei vertOffset);
	void SetNextRenderInfoPtr(RenderInfo * info);

	GLsizei CalculateVertOffset();
	
	GLsizei CalculateIndexOffsetBytes();
	//GLsizei GetVertOffset();
};

#endif //def RENDER_INFO_H


