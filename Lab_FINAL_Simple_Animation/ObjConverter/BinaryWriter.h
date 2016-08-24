#ifndef  BINARY_WRITER_H
#define BINARY_WRITER_H

//Kyle St.Amant
//7/18/2016
//description here
#include <fstream>

#pragma warning(push)  //Save state
#pragma warning(disable:4127) //disable warning
#pragma warning(disable:4251)
#pragma warning(disable:4100)
#pragma warning(disable:4201)
#include "GL\glew.h"
#pragma warning(pop) 
#include "IndexSizeInBytesEnum.h"
#include "RenderInfo.h"
class Mesh;
struct ColorVertex;
class BinaryWriter
{
public:
	bool WriteCustomBinaryFile(const char * filename, Mesh * pMesh);

private:
	int WriteMeshData	(std::ofstream &out, Mesh *			pMesh);
	int WriteRenderData (std::ofstream & out, RenderInfo * pRenderInfo);
	//int WriteRenderData(std::ofstream & out, Mesh * pMesh);
	int WriteVertData(std::ofstream & out, int stride, int numVerts, void * pVerts);

	int WriteIndexData(std::ofstream & out, int numIndices, void * pIndices, IndexSizeInBytesEnum isb);
	int WriteInt		(std::ofstream &out, int			value);
};

#endif //def BINARY_WRITER_H


