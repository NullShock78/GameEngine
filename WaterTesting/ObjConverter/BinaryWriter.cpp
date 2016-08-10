#include "BinaryWriter.h"

#include "GameLogger.h"
#include "Mesh.h"

bool BinaryWriter::WriteCustomBinaryFile(const char * filename, Mesh * pMesh)
{

	printf("--------------------------(%s)\n", filename);
	int totalBytes = 0;

	std::ofstream outputStream(filename, std::ios::binary | std::ios::out);

	if (!outputStream) 
	{
		GameLogger::Log(LogMsgType::cError, "BinaryWriter::WriteCustomBinaryFile() Unable to open [%s]", filename);
	}

	outputStream.seekp(0);
	WriteInt(outputStream, totalBytes);

	Mesh meshCopy = *pMesh;

	//memset(meshCopy.GetRenderInfo(), 0, sizeof(meshCopy.GetRenderInfo()));

	//meshCopy.m_indices = nullptr;
	//meshCopy.m_mesh = nullptr;


	totalBytes += WriteMeshData(outputStream, &meshCopy);
	totalBytes += WriteRenderData(outputStream, meshCopy.GetRenderInfo());
	totalBytes += WriteVertData(outputStream,meshCopy.GetNumVerts(),meshCopy.GetStride() ,(void*)meshCopy.GetVertexData());
	totalBytes += WriteIndexData(outputStream,meshCopy.GetNumIndices() , meshCopy.GetIndexDataStart(),pMesh->m_indexSizeEnum);

	//Seek to beginning of file
	outputStream.seekp(0);
	WriteInt(outputStream, totalBytes);

	outputStream.close();

	printf("Total\t\t: Wrote %d bytes.\n", totalBytes);
	printf("--------------------------\n");
	printf("\n\n\nGetIndexSizeEnum: %u\n\n\n", meshCopy.GetIndexSizeEnum());

	return true;
}

int BinaryWriter::WriteMeshData(std::ofstream & out, Mesh * pMesh)
{
	int size = sizeof(*pMesh);
	out.write(reinterpret_cast<char*>(pMesh), size);

	printf("Header\t\t: Wrote %4d bytes\n", size);
	return size;
}

int BinaryWriter::WriteRenderData(std::ofstream & out, RenderInfo * pRenderInfo)
{
	int size = sizeof(*pRenderInfo);
	out.write(reinterpret_cast<char*>(pRenderInfo), size);

	printf("RenderInfo\t\t: Wrote %4d bytes\n", size);
	return size;
}


int BinaryWriter::WriteVertData(std::ofstream & out,int stride , int numVerts,void * pVerts)
{
	int size = stride * numVerts;
	out.write(reinterpret_cast<char*>(pVerts), size);

	printf("Verts\t\t: Wrote %4d bytes\n", size);
	return size;
}

int BinaryWriter::WriteIndexData(std::ofstream & out, int numIndices, void * pIndices,IndexSizeInBytesEnum isb)
{
	int size = (int)isb * numIndices;
	out.write(reinterpret_cast<char*>(pIndices), size);
	printf("Indices\t\t: Wrote %4d bytes\n", size);
	return size;
}

int BinaryWriter::WriteInt(std::ofstream & out, int value)
{
	int size = sizeof(value);
	out.write(reinterpret_cast<char*>(&value), size);
	printf("Int\t\t: Wrote %4d bytes\n", size);
	return size;
}
