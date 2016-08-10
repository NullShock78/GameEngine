#ifndef  OBJ_CONVERTER_H
#define OBJ_CONVERTER_H

//Kyle St.Amant
//7/20/2016
//description here

#pragma warning(push)  //Save state
#pragma warning(disable:4127) //disable warning
#pragma warning(disable:4251)
#pragma warning(disable:4100)
#pragma warning(disable:4201)
#include "GL\glew.h"
#include "vec3.hpp"
#pragma warning(pop) 

#include <sstream>
#include <istream>
#include "Mesh.h"
#include "BinaryWriter.h"
#include "IndexSizeInBytesEnum.h"

typedef struct { float f1, f2, f3; } Pos3; // 3 floats per pos
typedef struct { float f1, f2, f3; } Col3;
typedef struct { float f1, f2; } Tex2; // 2 floats per texcoord
typedef struct { float f1, f2, f3; } Norm3; // 3 floats per pos
typedef struct { glm::vec3 p1, p2, p3; } Facet3; // 3 points per Facet
typedef struct { int a1, a2, a3; } Index3;


typedef struct { int a1, a2; } Index2;

typedef struct { Pos3 pos; Tex2 tex; } VertTexPair;
typedef struct { Pos3 pos; Tex2 tex; Norm3 norm; } VertTexNorm;
typedef struct { Pos3 pos;  Norm3 norm; } VertNormPair;
typedef struct { Pos3 pos; Col3 col;  Norm3 norm; } VertColNorm;
typedef struct { Pos3 pos; Col3 col; Tex2 tex;  Norm3 norm; } VertColTexNorm;



class ConfigReader;
struct ColorVertex;

class ObjConverter
{
private:
	int m_shaderID;
	BinaryWriter m_writer;
	char * m_data;
	const char * m_vertexType;
	static const int pathLen = 100;
	const char * inFilePathPtr;
	char m_inFilePath[pathLen]{ '\0' };

	const char * outFilePathPtr;
	char m_outFilePath[pathLen]{ '\0' };

	char m_modelConfKeys[pathLen]{ '\0' };

	int m_numVerts;
	int m_numIndices;

	int m_numTexcoords;
	int m_numNormals{ 0 };

	int m_lines;
	bool m_randCols{ false };
	bool m_analyze;

	float r{ 0 }; 
	float g{ 0 }; 
	float b{ 0 };

	//const char * m_filePath;
	
	Mesh m_mesh;
	//Current index
	int m_curInds;
	//Current vert
	int m_curVerts;
	int m_curTexcoords;

	int m_currentVertTexPair{ 0 };


	const char * modelNamePtr;
	glm::vec3 m_color{ glm::vec3() };
	ColorVertex * m_currentColorVertexArray;

	int m_curPos{ 0 };
	int m_curTex{ 0 };
	int m_curNorm{ 0 };

	Pos3    * m_unarrangedPositionArray;
	Tex2	* m_unarrangedTexCoordArray;
	Norm3	* m_unarrangedNormalArray;



	Index3 * m_multIndexArray;
	VertTexPair * m_vertTexPairArray;
	VertNormPair * m_vertNormPairArray;
	VertTexNorm * m_vertTexNormArray;
	GLfloat * m_finalVertexArray;
	


	GLuint * m_currentIndexArray; 
	ConfigReader * m_configReader;
	VertexFormats m_vertexFormat;

	void PutTogetherVertTex();
	void PutTogetherVertNorm();
	void PutTogetherVertTexNorm();
public:
	bool InitializeAndRun(ConfigReader * confReader);
	bool ShutDown();
	//bool GetFloats(const char * line, int numFloats, float * values);
	bool ReadFile(const char * fileName);

private:
	void ParseIndices(std::istringstream & stream);
	//void ParseVetrtexPositions(std::istringstream & stream);
	//bool AnalyzeData(const char * fileName);
	IndexSizeInBytesEnum GetIndexSize(int numIndices);

	bool ProcessFile(std::ifstream & stream);// const char * data);
	bool ProcessLine(const char * line);
};

#endif //def OBJ_CONVERTER_H


