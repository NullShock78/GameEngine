#include "ObjConverter.h"
#include "GameLogger.h"
#include "ColorVertex.h"
#include "ConfigReader.h"
#pragma warning(push)  //Save state
#pragma warning(disable:4201) //disable warnings
#include "gtc/random.hpp"
#pragma warning(pop)

const int ObjConverter::pathLen;


void ObjConverter::PutTogetherVertOnly()
{
	for (int j = 0; j < m_numIndices; ++j)
	{
		m_finalPosArray[j] = { m_unarrangedPositionArray[m_multIndexArray[j].a1] };
	}
	m_finalVertexArray = &m_finalPosArray[0].f1;
}

void ObjConverter::PutTogetherVertTex()
{
	//int curPair = 0;
	for (int j = 0; j < m_numIndices; ++j)
	{
		//int i = m_vertTexArray[j].a2;
		m_vertTexPairArray[j] = { m_unarrangedPositionArray[m_multIndexArray[j].a1],m_unarrangedTexCoordArray[m_multIndexArray[j].a2] };
		//printf("%f\n", m_vertTexPairArray[j].pos.f1);
		//printf("%f\n", m_vertTexPairArray[j].pos.f2);
		//printf("%f\n", m_vertTexPairArray[j].pos.f3);
		//printf("%f\n", m_vertTexPairArray[j].tex.f1);
		//printf("%f\n", m_vertTexPairArray[j].tex.f2);
		/*printf("RAW:%f\n", m_unarrangedTexCoordArray[m_vertTexArray[j].a2].f1);
		printf("RAW:%f\n", m_unarrangedTexCoordArray[m_vertTexArray[j].a2].f2);
		i = i + 1;*/
	}
	m_finalVertexArray = &m_vertTexPairArray[0].pos.f1;
}



void ObjConverter::PutTogetherVertNorm()
{
	
	//int curPair = 0;
	for (int j = 0; j < m_numIndices; ++j)
	{
		//int i = m_vertTexArray[j].a2;
		m_vertNormPairArray[j] = { m_unarrangedPositionArray[m_multIndexArray[j].a1],m_unarrangedNormalArray[m_multIndexArray[j].a3]};
		
		if ((j + 1) % 3 == 0)
		{
			//0,1, 0,2

			glm::vec3 pos1 = glm::vec3(m_vertNormPairArray[j - 2].pos.f1, m_vertNormPairArray[j - 2].pos.f2, m_vertNormPairArray[j - 2].pos.f3);
			glm::vec3 pos2 = glm::vec3(m_vertNormPairArray[j - 1].pos.f1, m_vertNormPairArray[j - 1].pos.f2, m_vertNormPairArray[j - 1].pos.f3);
			glm::vec3 pos3 = glm::vec3(m_vertNormPairArray[j].pos.f1, m_vertNormPairArray[j].pos.f2, m_vertNormPairArray[j].pos.f3);

			glm::vec3 norm = glm::normalize( glm::cross(pos2 - pos1, pos3 - pos1));
			Norm3 t_norm = { norm.x,norm.y,norm.z };
			m_vertNormPairArray[j - 2].norm = t_norm;
			m_vertNormPairArray[j - 1].norm = t_norm;
			m_vertNormPairArray[j].norm = t_norm;
		}
		
		//printf("%f\n", m_vertTexPairArray[j].pos.f1);
		//printf("%f\n", m_vertTexPairArray[j].pos.f2);
		//printf("%f\n", m_vertTexPairArray[j].pos.f3);
		//printf("%f\n", m_vertTexPairArray[j].tex.f1);
		//printf("%f\n", m_vertTexPairArray[j].tex.f2);
		/*printf("RAW:%f\n", m_unarrangedTexCoordArray[m_vertTexArray[j].a2].f1);
		printf("RAW:%f\n", m_unarrangedTexCoordArray[m_vertTexArray[j].a2].f2);
		i = i + 1;*/
	}
	m_finalVertexArray = &m_vertTexPairArray[0].pos.f1;
}

void ObjConverter::PutTogetherVertTexNorm()
{
	//int curPair = 0;
	for (int j = 0; j < m_numIndices; ++j)
	{
		//int i = m_vertTexArray[j].a2;
		m_vertTexNormArray[j] = { m_unarrangedPositionArray[m_multIndexArray[j].a1],m_unarrangedTexCoordArray[m_multIndexArray[j].a2],m_unarrangedNormalArray[m_multIndexArray[j].a3] };
		//if ((j + 1) % 3 == 0)
		//{
		//	//0,1, 0,2

		//	glm::vec3 pos1 = glm::vec3(m_vertTexNormArray[j - 2].pos.f1, m_vertTexNormArray[j - 2].pos.f2, m_vertTexNormArray[j - 2].pos.f3);
		//	glm::vec3 pos2 = glm::vec3(m_vertTexNormArray[j - 1].pos.f1, m_vertTexNormArray[j - 1].pos.f2, m_vertTexNormArray[j - 1].pos.f3);
		//	glm::vec3 pos3 = glm::vec3(m_vertTexNormArray[j].pos.f1, m_vertTexNormArray[j].pos.f2, m_vertTexNormArray[j].pos.f3);

		//	glm::vec3 norm = glm::normalize(glm::cross(pos2 - pos1, pos3 - pos1));
		//	Norm3 t_norm = { norm.x,norm.y,norm.z };
		//	m_vertTexNormArray[j - 2].norm = t_norm;
		//	m_vertTexNormArray[j - 1].norm = t_norm;
		//	m_vertTexNormArray[j].norm = t_norm;
		//}

		
	}
	m_finalVertexArray = &m_vertTexPairArray[0].pos.f1;
}

//void ObjConverter::PutTogetherVertColTexNorm()
//{
//	//int curPair = 0;
//	for (int j = 0; j < m_numIndices; ++j)
//	{
//		//int i = m_vertTexArray[j].a2;
//		//m_vertColTexNormArray[j] = { m_unarrangedPositionArray[m_multIndexArray[j].a1],m_unarrangedTexCoordArray[m_multIndexArray[j].a2] };
//		//printf("%f\n", m_vertTexPairArray[j].pos.f1);
//		//printf("%f\n", m_vertTexPairArray[j].pos.f2);
//		//printf("%f\n", m_vertTexPairArray[j].pos.f3);
//		//printf("%f\n", m_vertTexPairArray[j].tex.f1);
//		//printf("%f\n", m_vertTexPairArray[j].tex.f2);
//		/*printf("RAW:%f\n", m_unarrangedTexCoordArray[m_vertTexArray[j].a2].f1);
//		printf("RAW:%f\n", m_unarrangedTexCoordArray[m_vertTexArray[j].a2].f2);
//		i = i + 1;*/
//	}
//	m_finalVertexArray = &m_vertColTexNormArray[0].pos.f1;
//}


bool ObjConverter::InitializeAndRun(ConfigReader * confReader)
{
	m_numVerts = 0;
	m_numIndices = 0;
	m_lines = 0;

	m_analyze = false;
	//m_analyze = false;

	if (!confReader->GetBoolForKey("ObjConverter.Mode.Analyze",m_analyze,true)) return false;


	if (!confReader->GetStringForKey("ObjConverter.Obj.InputFileFolder", inFilePathPtr)) {
		GameLogger::Log(LogMsgType::cFatalError, "ObjConverter::Initialize: input file folder invalid.");
		return false;
	}
	if (!confReader->GetStringForKey("ObjConverter.Scene.OutputFileFolder", outFilePathPtr)) {
		GameLogger::Log(LogMsgType::cFatalError, "ObjConverter::Initialize: output file folder invalid.");
		return false;
	}
	if (!confReader->GetStringForKey("ObjConverter.Model", modelNamePtr)) {
		GameLogger::Log(LogMsgType::cFatalError, "ObjConverter::Initialize: Model Name invalid.");
		return false;
	}

	if (!confReader->GetIntForKey("ObjConverter.Shader", m_shaderID)) {
		GameLogger::Log(LogMsgType::cFatalError, "ObjConverter::Initialize: Shader num invalid.");
		return false;
	}

	snprintf(m_modelConfKeys, pathLen, "ObjConverter.Model.%s.NumVerts",modelNamePtr);
	if (!confReader->GetIntForKey(m_modelConfKeys, m_numVerts)) {
		GameLogger::Log(LogMsgType::cFatalError, "ObjConverter::Initialize: %s invalid.", m_modelConfKeys);
		return false;
	}

	snprintf(m_modelConfKeys, pathLen, "ObjConverter.Model.%s.NumIndices", modelNamePtr);
	if (!confReader->GetIntForKey(m_modelConfKeys, m_numIndices)) {
		GameLogger::Log(LogMsgType::cFatalError, "ObjConverter::Initialize: %s invalid.", m_modelConfKeys);
		return false;
	}

	snprintf(m_modelConfKeys, pathLen, "ObjConverter.Model.%s.NumNormals", modelNamePtr);
	if (!confReader->GetIntForKey(m_modelConfKeys, m_numNormals)) {
		GameLogger::Log(LogMsgType::cFatalError, "ObjConverter::Initialize: %s invalid.", m_modelConfKeys);
		return false;
	}

	if (!confReader->GetStringForKey("ObjConverter.Mode.VertexType",m_vertexType)) {
		GameLogger::Log(LogMsgType::cFatalError, "ObjConverter::Initialize: ObjConverter.Mode.VertexType invalid.", m_modelConfKeys);
		return false;
	}
	//TODO: method-ify
	snprintf(m_modelConfKeys, pathLen, "ObjConverter.Model.%s.NumTexCoords", modelNamePtr);
	if (!confReader->GetIntForKey(m_modelConfKeys, m_numTexcoords)) {
		GameLogger::Log(LogMsgType::cFatalError, "ObjConverter::Initialize: %s invalid.", m_modelConfKeys);
		return false;
	}


	if (strcmp(m_vertexType, "pc") == 0)
	{
		m_vertexFormat = VertexFormats::PositionColor;
	}
	else if (strcmp(m_vertexType, "p") == 0)
	{
		m_vertexFormat	= VertexFormats::PositionOnly;
		m_unarrangedPositionArray = new Pos3[m_numVerts];
		m_finalPosArray = new Pos3[m_numIndices];
		m_multIndexArray = new Index3[m_numIndices]{ 0,0,0 };


	}
	else if (strcmp(m_vertexType, "pt") == 0)
	{
		m_vertexFormat = VertexFormats::PositionTexture;
		//m_vertTexArray				= new VertTex2[m_numIndices];
		m_curTex = 0;
		m_unarrangedTexCoordArray	= new Tex2[m_numTexcoords];
		m_unarrangedPositionArray	= new Pos3[m_numVerts];

		m_multIndexArray			= new Index3[m_numIndices]{ 0,0,0 };
		m_vertTexPairArray			= new VertTexPair[m_numIndices]{ {0,0,0},{0,0} };
	}
	else if (strcmp(m_vertexType, "ptn") == 0)
	{
		m_vertexFormat = VertexFormats::PositionTextureNormal;
		m_unarrangedTexCoordArray = new Tex2[m_numTexcoords];
		m_unarrangedPositionArray = new Pos3[m_numVerts];
		m_unarrangedNormalArray = new Norm3[m_numNormals];
		m_vertTexNormArray = new VertTexNorm[m_numIndices];
		//m_unarrangedNormalArray = new Norm3[]
		m_multIndexArray = new Index3[m_numIndices]{ 0,0,0 };


	}
	else if (strcmp(m_vertexType, "pn") == 0)
	{
		m_vertexFormat = VertexFormats::PositionNormal;
		m_unarrangedPositionArray = new Pos3[m_numVerts];
		m_unarrangedNormalArray = new Norm3[m_numNormals];
		m_vertNormPairArray = new VertNormPair[m_numIndices];
		m_multIndexArray = new Index3[m_numIndices]{ 0,0,0 };
	}
	else if (strcmp(m_vertexType, "pct") == 0)
	{
		m_vertexFormat = VertexFormats::PositionColorTexture;
	}
	else if (strcmp(m_vertexType, "pctn") == 0)
	{
		m_vertexFormat = VertexFormats::PositionColorTextureNormal;

	}
	else
	{
		GameLogger::Log(LogMsgType::cFatalError, "Config val for vertexType is invalid");
		return false;
	}

	const char * colorCheck;
	if (!confReader->GetStringForKey("ObjConverter.Color", colorCheck)) return false;
	if ( strcmp(colorCheck, "random") == 0)
	{
		m_randCols = true;
	}
	else
	{
		if (!confReader->GetFloatsForKey("ObjConverter.Color", 3, &r))return false;
	}
	
	//Set in and out paths
	snprintf(m_inFilePath, pathLen, "%s%s.obj", inFilePathPtr,modelNamePtr);
	snprintf(m_outFilePath, pathLen, "%s%s.%s.scene", outFilePathPtr, modelNamePtr, m_vertexType);

	//int ptrPos = 0;
	//if (!confReader->DupStringForKey("ObjConverter.Obj.InputFilename", filePathPtr, buffSize, ptrPos)) return false;
	//filePathPtr += ptrPos;
	//if (!confReader->DupStringForKey("ObjConverter.Model", filePathPtr, (buffSize-ptrPos), ptrPos)) return false;

	m_curInds = 0;
	m_curVerts = 0;

	//m_numTexcoords = 0;

	m_curTexcoords = 0;
	//m_numTexcoords
	
		bool finishedSuccessfully = ReadFile(m_inFilePath);



		GameLogger::Log(LogMsgType::cInfo, "NUM VERTS:     %d", m_numVerts);
		GameLogger::Log(LogMsgType::cInfo, "NUM INDICES:   %d", m_numIndices);
		GameLogger::Log(LogMsgType::cInfo, "NUM TEXCOORDS: %d", m_numTexcoords);
		GameLogger::Log(LogMsgType::cInfo, "NUM NORMALS:   %d", m_numNormals);
		if (!finishedSuccessfully) { 
			GameLogger::Log(LogMsgType::cFatalError, "ObjConverter::InitializeAndRun(): Did not finish successfully.");
			return false; 
		}

	return true;
}

IndexSizeInBytesEnum ObjConverter::GetIndexSize(int numIndices)
{
	if (numIndices <= static_cast<int>(ModelSize::Small))
		return IndexSizeInBytesEnum::Ubyte;
	if (numIndices <= static_cast<int>(ModelSize::Medium))
		return IndexSizeInBytesEnum::Ushort;
	return IndexSizeInBytesEnum::Uint;
}


bool ObjConverter::ShutDown()
{
	delete[] m_currentColorVertexArray;
	delete[] m_currentIndexArray;

	if (m_vertexFormat == VertexFormats::PositionOnly)
	{
		delete[] m_finalPosArray;
	}


	if (m_vertexFormat == VertexFormats::PositionTexture)
	{
		delete[] m_multIndexArray;
		delete[] m_unarrangedPositionArray;
		delete[] m_unarrangedTexCoordArray;
		delete[] m_vertTexPairArray;
	}

	if (m_vertexFormat == VertexFormats::PositionNormal)
	{
		delete[] m_unarrangedPositionArray;
		delete[] m_unarrangedNormalArray;
		delete[] m_vertNormPairArray;
		delete[] m_multIndexArray;
	}

	if (m_vertexFormat == VertexFormats::PositionTextureNormal)
	{
		delete[] m_multIndexArray;
		delete[] m_unarrangedPositionArray;
		delete[] m_unarrangedTexCoordArray;
		delete[] m_unarrangedTexCoordArray;
		delete[] m_vertTexNormArray;
	}

	//delete[] m_filePath;
	return false;
}

//bool ObjConverter::GetFloats(const char * line, int numFloats, float * values) {
//
//	if (numFloats == 0)
//	{
//		//GameLogger::Log(LogMsgType::cFatalError, "ConfigReader::GetFloatsForKey(): 0 floats requested for key %s, aborting.", key);
//		return false;
//	}
//
//	const char * valToParse;
//	//GetStringForKey(key, valToParse);
//
//	std::istringstream strStream = std::istringstream(valToParse);
//
//	for (int j = 0; j < numFloats; j++)
//	{
//		std::string  temp;
//		if (!(strStream >> temp))
//		{
//			//GameLogger::Log(LogMsgType::cFatalError, "ConfigReader::GetFloatsForKey(): Key %s: not enough floats! [%d] floats requested, [%d] floats found. aborting.", key, numFloats, j - 1);
//			return false;
//		}
//
//		*values = (float)std::atof(valToParse);
//		++values;
//
//	}
//	return true;
//}


bool ObjConverter::ReadFile(const char * fileName)
{
	
	std::ifstream m_myFile;
	m_myFile.open(fileName, std::ios::in);
	
	if (!m_myFile)
	{
		//GameLogger::Log(LogMsgType::FatalError, "ConfigReader failed to open the file [%s] for reading, check the path.\n", filename);
		GameLogger::Log(LogMsgType::cFatalError, "ObjConverter::ReadFile(): Failed to open  %s",fileName);
		return false;
	}

	if (!ProcessFile(m_myFile))
	{
		GameLogger::Log(LogMsgType::cFatalError, "ObjConverter::ReadFile(): ProcessFile failed.");

		return false;
	}
	GameLogger::Log(LogMsgType::cInfo, "ObjConverter::ReadFile() Read file %s successfully", fileName);

	return true;
}



//---------------------------------------------------------------CURRENT ISSUE---------------------------------------------
//---------------------------------------------------------------CURRENT ISSUE---------------------------------------------
//---------------------------------------------------------------CURRENT ISSUE---------------------------------------------
//---------------------------------------------------------------CURRENT ISSUE---------------------------------------------
//	RESOLVED:		//ONLY READS FIRST INT IN INDEX line.
//					//Example:
//					//f 1/5/5 2/6/6 5/10/7 reads to
//					//1,1,1
//---------------------------------------------------------------CURRENT ISSUE---------------------------------------------
//---------------------------------------------------------------CURRENT ISSUE---------------------------------------------
//---------------------------------------------------------------CURRENT ISSUE---------------------------------------------
//---------------------------------------------------------------CURRENT ISSUE---------------------------------------------
void ObjConverter::ParseIndices(std::istringstream & stream)
{
	std::string s;
	int index = 0;
	int garbage = 0;

	char c = 'c';

	stream >> s;
	std::istringstream f(s);
	f >> index;
	--index;

	m_currentIndexArray[m_curInds] = index;

	//if (m_vertexFormat == VertexFormats::PositionTexture) {
		m_multIndexArray[m_curInds].a1 = index;

	//}


	//GameLogger::Log(LogMsgType::ConsoleOnly, "f1: %d", index);
	//while (f.peek() != ' ' | '	') {
	//	if (f.peek() == '/')
	//	{
	//		//eat char
	//		f >> c;
	//	}
	//	else if (f.peek() != ' ' | '	' | '\0')
	//	{
	//		f >> garbage;
	//	}
	//}


	f >> c;

	if ((int)m_vertexFormat & (int)VertexFormats::HasTexture) {
		f >> index;
		--index;
		m_multIndexArray[m_curInds].a2 = index;
	}
	else
	{
		f >> garbage;
	}
	f >> c;
	if ((int)m_vertexFormat & (int)VertexFormats::HasNormal) {
		f >> index;
		--index;
		m_multIndexArray[m_curInds].a3 = index;
	}

	if (f.peek() != ' ' && f.peek() != '	')
	{
		f >> garbage;
	}
	if (f.peek() != ' ' && f.peek() != '	')
	{
		f >> garbage;
	}
	
	++m_curInds;

	stream >> s;
	std::istringstream f2(s);
	f2 >> index;
	--index;
	m_currentIndexArray[m_curInds] = index;
	//if (m_vertexFormat == VertexFormats::PositionTexture) {
		m_multIndexArray[m_curInds].a1 = index;
	//}

		

	f2 >> c;

	if ((int)m_vertexFormat & (int)VertexFormats::HasTexture) {
		f2 >> index;
		--index;
		m_multIndexArray[m_curInds].a2 = index;
	}
	else
	{
		f2 >> garbage;
	}
	f2 >> c;
	if ((int)m_vertexFormat & (int)VertexFormats::HasNormal) {
		f2 >> index;
		--index;
		m_multIndexArray[m_curInds].a3 = index;
	}

	if (f.peek() != ' ' && f.peek() != '	')
	{
		f2 >> garbage;
	}
	if (f.peek() != ' ' && f.peek() != '	')
	{
		f2 >> garbage;
	}
	++m_curInds;
	
	//GameLogger::Log(LogMsgType::ConsoleOnly, "f2: %d", index);
	stream >> s;
	std::istringstream f3(s);
	f3 >> index;
	--index;
	m_currentIndexArray[m_curInds] = index;
	
	//if ((int)m_vertexFormat & (int)VertexFormats::HasTexture) {
		m_multIndexArray[m_curInds].a1 = index;
	//}
	//GameLogger::Log(LogMsgType::ConsoleOnly, "f3: %d", index);
		f3 >> c;
		if ((int)m_vertexFormat & (int)VertexFormats::HasTexture) {
			f3 >> index;
			--index;
			m_multIndexArray[m_curInds].a2 = index;
		}
		f3 >> c;
		if ((int)m_vertexFormat & (int)VertexFormats::HasNormal) {
			f3 >> index;
			--index;
			m_multIndexArray[m_curInds].a3 = index;
		}
		++m_curInds;
	
}

//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------



//void ObjConverter::ParseVetrtexPositions(std::ifstream & stream)
//{
//	//float f1,
//
//
//}



bool ObjConverter::ProcessFile(std::ifstream & stream)
{



	m_currentColorVertexArray = new ColorVertex[m_numVerts];
	m_currentIndexArray = new GLuint[m_numIndices];

	const int lineSize = 512;
	char line[lineSize];
	while (stream.getline(line, lineSize))
	{
		if (!ProcessLine(line))
		{
			GameLogger::Log(LogMsgType::cFatalError, "ObjConverter::ProcessFile(): ProcessLine() failed");
			stream.close();
			return false;
		}

	}
	
	if (!m_analyze) {
		//Uint for now

		if (m_vertexFormat == VertexFormats::PositionTexture) {
			PutTogetherVertOnly();
			m_mesh.SetData(&m_finalPosArray[0].f1, m_numIndices, m_currentIndexArray, 0, IndexSizeInBytesEnum::Uint, glm::vec3(0, 0, 0), VertexFormats::PositionOnly);
			m_mesh.m_secondIndexed = false;
			m_mesh.m_renderInfo.m_indexed = false;
			printf("STRIDE before: %d\n", m_mesh.m_renderInfo.m_stride);
			m_mesh.m_renderInfo.m_vertexFormat = VertexFormats::PositionOnly;
			m_mesh.m_renderInfo.m_stride = 5 * sizeof(GLfloat);
			printf("STRIDE after: %d\n", m_mesh.m_renderInfo.m_stride);
			
			m_mesh.m_renderInfo.m_wroteShader = 0;
			m_mesh.m_renderInfo.m_shader = 0;



		}
		else if (m_vertexFormat == VertexFormats::PositionTexture) {
			PutTogetherVertTex();
			m_mesh.SetData(&m_vertTexPairArray[0].pos.f1, m_numIndices, m_currentIndexArray, 0, IndexSizeInBytesEnum::Uint, glm::vec3(0, 0, 0), VertexFormats::PositionTexture);
			m_mesh.m_secondIndexed = false;
			m_mesh.m_renderInfo.m_indexed = false;
			printf("STRIDE before: %d\n", m_mesh.m_renderInfo.m_stride);
			m_mesh.m_renderInfo.m_vertexFormat = VertexFormats::PositionTexture;
			m_mesh.m_renderInfo.m_stride = 5 * sizeof(GLfloat);
			printf("STRIDE after: %d\n", m_mesh.m_renderInfo.m_stride);

		
			m_mesh.m_renderInfo.m_wroteShader = m_shaderID;
			m_mesh.m_renderInfo.m_shader = m_shaderID;


			//printf("m_indexed before: %d\n", m_mesh.m_renderInfo.m_indexed);
		}
		else if (m_vertexFormat == VertexFormats::PositionNormal) {
			PutTogetherVertNorm();
			m_mesh.SetData(&m_vertNormPairArray[0].pos.f1, m_numIndices, m_currentIndexArray, 0, IndexSizeInBytesEnum::Uint, glm::vec3(0, 0, 0), m_vertexFormat);
			m_mesh.m_secondIndexed = false;
			m_mesh.m_renderInfo.m_vertexFormat = VertexFormats::PositionNormal;
			m_mesh.m_renderInfo.m_indexed = false;
			printf("STRIDE before: %d\n", m_mesh.m_renderInfo.m_stride);
			m_mesh.m_renderInfo.m_stride = 6 * sizeof(GLfloat);
			printf("STRIDE after: %d\n", m_mesh.m_renderInfo.m_stride);

			//TODO: Set default shader in config
			m_mesh.m_renderInfo.m_wroteShader = m_shaderID;
			m_mesh.m_renderInfo.m_shader = m_shaderID;


			//printf("m_indexed before: %d\n", m_mesh.m_renderInfo.m_indexed);
		}
		else if (m_vertexFormat == VertexFormats::PositionTextureNormal) {
			PutTogetherVertTexNorm();
			m_mesh.SetData(&m_vertTexNormArray[0].pos.f1, m_numIndices, m_currentIndexArray, 0, IndexSizeInBytesEnum::Uint, glm::vec3(0, 0, 0), m_vertexFormat);
			m_mesh.m_secondIndexed = false;
			m_mesh.m_renderInfo.m_indexed = false;
			m_mesh.m_renderInfo.m_vertexFormat = VertexFormats::PositionTextureNormal;
			printf("STRIDE before: %d\n", m_mesh.m_renderInfo.m_stride);
			m_mesh.m_renderInfo.m_stride = 8 * sizeof(GLfloat);
			printf("STRIDE after: %d\n", m_mesh.m_renderInfo.m_stride);

			//TODO: Set default shader in config
			m_mesh.m_renderInfo.m_wroteShader = m_shaderID;
			m_mesh.m_renderInfo.m_shader = m_shaderID;


			//printf("m_indexed before: %d\n", m_mesh.m_renderInfo.m_indexed);
		}
		else
		{
			m_mesh.SetData(m_currentColorVertexArray, m_numVerts, m_currentIndexArray, m_numIndices, IndexSizeInBytesEnum::Uint, glm::vec3(0, 0, 0), m_vertexFormat);
			m_mesh.m_renderInfo.m_shader = m_shaderID;
			m_mesh.m_renderInfo.m_wroteShader = m_shaderID;
		}
		//printf("\n\n\nWriting: IndexSizeInBytesEnum: %d\n\n\n", IndexSizeInBytesEnum::Uint);
		if (!m_writer.WriteCustomBinaryFile(m_outFilePath, &m_mesh)) {
			return false;
		}
	}
	


	return true;
}



bool ObjConverter::ProcessLine(const char * line)
{
	std::string word;
	std::istringstream * parsePtr = new std::istringstream(line);
	std::istringstream & parse = *parsePtr;
	//parse(line);
	parse >> word;
	



	if (word[0] == '#')
	{
		//Skip over it

	}
	else if (word == "v")
	{

		if (m_analyze)
		{
			++m_numVerts;
			//printf("NumVerts: %d", m_numVerts);
			return true;
		}


		float f1, f2, f3;
		parse >> f1 >> f2 >> f3;
		//GameLogger::Log(LogMsgType::ConsoleOnly, "v: %f,%f,%f", f1, f2, f3);
		if (m_vertexFormat == VertexFormats::PositionColor)
		{
			if (m_randCols) {
				m_currentColorVertexArray[m_curVerts] = { glm::vec3(f1,f2,f3), glm::vec3(glm::linearRand(0.01f, 1.0f),glm::linearRand(0.01f, 1.0f),glm::linearRand(0.01f, 1.0f)) };
			}
			else
			{
				m_currentColorVertexArray[m_curVerts] = { glm::vec3(f1,f2,f3), glm::vec3(r,g,b) };
			}
		
		}
		else
		{
			m_unarrangedPositionArray[m_curPos] = { f1, f2, f3 };
			++m_curPos;
		}

	++m_curVerts;
	}
	else if (strcmp(word.c_str(), "vt") == 0)
	{
		if (m_analyze)
		{
			++m_numTexcoords;
			//printf("NumVerts: %d", m_numVerts);
			return true;
		}
		if ((int)m_vertexFormat & (int)VertexFormats::HasTexture)
		{

			float f1, f2;
			parse >> f1 >> f2;

			m_unarrangedTexCoordArray[m_curTex] = { f1,f2 };

			++m_curTex;
		}

	}
	else if (strcmp(word.c_str(), "vn") == 0)
	{
		if (m_analyze)
		{
			++m_numNormals;
			//printf("NumVerts: %d", m_numVerts);
			return true;
		}

		if ((int)m_vertexFormat & (int)VertexFormats::HasNormal)
		{

			float f1, f2 , f3;
			parse >> f1 >> f2 >> f3;

			m_unarrangedNormalArray[m_curNorm] = { f1,f2,f3 };

			++m_curNorm;
		}

	}
	else if (word == "f")
	{

		if (m_analyze)
		{
			m_numIndices+=3;
			//printf("NumIndices: %d", m_numIndices);
			return true;
		}

			ParseIndices(parse);

		}

		//else
		//{
			//printf("%s\n", line);
		//}

	//delete &word;
	//parse.clear
	delete parsePtr;
	return true;
	}
