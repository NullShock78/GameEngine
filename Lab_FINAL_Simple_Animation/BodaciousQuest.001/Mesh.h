#ifndef  MESH_H
#define MESH_H

//Kyle St.Amant
//7/6/2016
//Mesh class, holds ColorVertex objects

#pragma warning(push)  																											 
#pragma warning(disable:4201) 																								 
#include "GL\glew.h"	
#include "vec3.hpp"
#include "ColorVertex.h"
#pragma warning(pop)						
#include "GameLogger.h"
#include "RenderInfo.h"
//#include "ColorVertex.h"

#include "IndexSizeInBytesEnum.h"
#include "ModelSize.h"
#include "VertexFormats.h"

// Vertices will always have Position and optionally may have any or all of the following: 
//        a color, a texture, a normal.
//    When we read or write a vertex, these various pieces will always occur in this order: 
//        Vertex, Color, Texture, Normal.
//    We may not need all of the 8 possible vertex combinations, but it not difficult 
//    to support them all if we do so in a structured manner.






class Mesh
{
public:
	void *	m_mesh;
	GLuint	m_numVerts;
	glm::vec3 m_colorTint;

	void *		m_indices{ nullptr };
	GLuint			m_numIndices;
	//-----------------------------------RENDER INFO------------
	RenderInfo m_renderInfo;
	//----------------------------------------------------------
	IndexSizeInBytesEnum m_indexSizeEnum{IndexSizeInBytesEnum::Uint};

	bool m_secondIndexed{true};
	


public: 

	Mesh() {};

	//Mesh(ColorVertex * colorVerts, GLuint numVerts, GLuint * indices, GLuint numIndices, glm::vec3 rgbTint = glm::vec3())
	//	:
	//	m_mesh(colorVerts),
	//	m_numVerts(numVerts),
	//	m_indices(indices),
	//	m_numIndices(numIndices),
	//	m_colorTint(rgbTint)
	//{}

public://funcs
	void SetRenderIndexSizeEnum(IndexSizeInBytesEnum val)
	{
		m_renderInfo.SetIndexSizeEnum(val);
	};

	IndexSizeInBytesEnum GetIndexSizeEnum()
	{
		return m_indexSizeEnum;
	};

	void SetData(void * colorVerts, GLuint numVerts, void * indices, GLuint numIndices, /*RenderInfo renderInfo,*/IndexSizeInBytesEnum indexSize = IndexSizeInBytesEnum::Uint, glm::vec3 rgbTint = glm::vec3(), VertexFormats vertFormat = VertexFormats::PositionColor)
	{
		m_mesh = colorVerts;
		//m_renderInfo.SetRenderInfo(renderInfo);  // = renderInfo;
		m_numVerts=numVerts;
		
		m_indices=indices;

		m_numIndices=numIndices;
		
		m_colorTint = rgbTint;
		
		m_indexSizeEnum = indexSize;

		m_renderInfo.m_isb = indexSize;
		m_renderInfo.m_stride = 0;
		if ((int)vertFormat & (int)VertexFormats::HasPosition) m_renderInfo.m_stride += 3 * sizeof(GLfloat);
		if ((int)vertFormat &  (int)VertexFormats::HasColor) m_renderInfo.m_stride += 3 * sizeof(GLfloat);
		if ((int)vertFormat &  (int)VertexFormats::HasTexture) m_renderInfo.m_stride += 2 * sizeof(GLfloat);
		if ((int)vertFormat &  (int)VertexFormats::HasNormal) m_renderInfo.m_stride += 3 * sizeof(GLfloat);
		///printf("\n\n\n\n\n\n\n\nSizeOf m_stride = [%d]\n\n\n\n\n\n\n\n", m_renderInfo.m_stride);
	};
	void * GetVertexData() {
		return m_mesh;
	};
	RenderInfo * GetRenderInfo()
	{
		return &m_renderInfo;
	};

	/*GLfloat * GetVertexDataStart() { 
		return &(*m_mesh).m_position.x;
	};*/
	void * GetVertexDataStart() {
		return m_mesh;
	};
	void * GetIndexDataStart() {
		return m_indices;
	};

	GLsizei GetStride()
	{
		return m_renderInfo.m_stride;//sizeof(*m_mesh);
	};

	GLsizei GetVertSizeInBytes()
	{
		return m_renderInfo.m_stride * m_numVerts;
	};

	GLsizei GetIndexSizeInBytes()
	{
		//-------------------------------------------------------------------------
		return (GLsizei)m_indexSizeEnum * m_numIndices;
	};

	GLsizei GetNumVerts()
	{
		return m_numVerts;
	};

	GLsizei GetNumIndices()
	{
		return m_numIndices;
	};

	void SetTint(glm::vec3 color) {
		m_colorTint = color;
	};

};

#endif //def MESH_H


