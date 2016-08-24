#include "RenderEngine.h"
#include "Mesh.h"
#include "GameLogger.h"
#include "BufferManager.h"
#include "GraphicalObject.h"
#include "ShaderProgram.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "MyGL.h"
GLuint RenderEngine::m_positionAttrib;
GLuint RenderEngine::m_colorAttrib;
GLuint RenderEngine::m_uniformLocCol;
GLuint RenderEngine::m_uniformLocMat4;
ShaderProgram * RenderEngine::m_shaderProgramPtr;
GLfloat tempLight[3] = { 0.0f, 1.0f, 0.0f };
GLfloat tempLightDir[3] = { 0.0f, -1.0f, 0.0f };

 //glm::vec3 tempLightDir = glm::vec3(0.1f, -1.0f, 0.1f);

GLenum RenderEngine::GetIndexType(IndexSizeInBytesEnum indexSize)
{
	//printf("\n\n\n\n\n\n\nAddMesh: INDEX SIZE ENUM Retrieved: %d\n\n\n\n\n\n", indexSize);


	switch (indexSize)
	{
	case IndexSizeInBytesEnum::Ubyte:  return GL_UNSIGNED_BYTE;
	case IndexSizeInBytesEnum::Ushort: return GL_UNSIGNED_SHORT;
	case IndexSizeInBytesEnum::Uint:   return GL_UNSIGNED_INT;
	default:
		GameLogger::Log(LogMsgType::cProgrammerError, "Unknown index size (%d) in GetIndexType ", indexSize);
		//return GL_UNSIGNED_INT;
		return GL_FALSE;
	}
}

bool RenderEngine::AttachLight(GraphicalObject * gob, /* TODO: Light class*/GraphicalObject * lightGob)
{
	gob->SetLight(lightGob);


	return false;
}

bool RenderEngine::SetUniformsShader0(GraphicalObject * gob, glm::mat4 screenMat)
{
	glUniform3fv(15, 1, (GLfloat*)gob->GetTint());
	glUniformMatrix4fv(16, 1, GL_FALSE, &screenMat[0][0]);
	return true;
}

bool RenderEngine::SetUniformsShader1(GraphicalObject * gob, glm::mat4 screenMat)
{
	glUniform3fv(15, 1, (GLfloat*)gob->GetTint());
	glUniformMatrix4fv(16, 1, GL_FALSE, &screenMat[0][0]);
	return true;
}

bool RenderEngine::SetUniformsShader2(GraphicalObject * gob, glm::mat4 screenMat)
{
	//glUniform3fv(15, 1, (GLfloat*)gob->GetTint());
	
	//TEXTURE
	glUniform1i(20, 0);
	glActiveTexture(GL_TEXTURE0);

	TextureManager::BindImageByID(gob->GetTexture());

	glUniformMatrix4fv(16, 1, GL_FALSE, &screenMat[0][0]);
	return true;
}

bool RenderEngine::SetUniformsShader4(GraphicalObject * gob, glm::mat4 screenMat)
{

	
	
	glUniform3fv(15, 1, (GLfloat*)gob->GetTint());
	if (MyGL::TestForError(LogMsgType::cFatalError, " uniLight failed")) return false;

	
	glUniformMatrix4fv(20, 1, GL_FALSE, &(gob->GetRotationMatrix() * gob->GetScaleMatrix())[0][0]);

	glUniform3fv(22, 1, &tempLight[0]);

	if (MyGL::TestForError(LogMsgType::cFatalError, "glUniform3fv(): 22, Temp light failed"))return false;
	glUniform3fv(23, 1, &tempLightDir[0]);
	//if (MyGL::TestForError(LogMsgType::cFatalError, "glUniform3fv(): 23, Temp light dir failed"))return false;
	//glUniform3fv(19, 1, (GLfloat*)&(gob->GetPos().x));

	float * pos = gob->GetPosX();
	glUniform3fv(19, 1, pos);
	glUniformMatrix4fv(16, 1, GL_FALSE, &screenMat[0][0]);
	return true;
}

bool RenderEngine::SetUniformsShader5(GraphicalObject * gob, glm::mat4 screenMat)
{
	static const GLfloat tempLight2[3] = { 0.0f, 1.0f, 0.0f };


	TextureManager::BindImageByID(gob->GetTexture());
	//glUniform1i(20 , gob->GetTexture());
	glUniformMatrix4fv(21, 1, GL_FALSE, &(gob->GetRotationMatrix() * gob->GetScaleMatrix())[0][0]);
	//23
	//	24
	glUniform3fv(23, 1, gob->GetPosX());
	glUniform3fv(24, 1, &tempLight2[0]);
	glUniform3fv(22, 1, &tempLight2[0]);
	
	if (MyGL::TestForError(LogMsgType::cFatalError, "glUniform3fv(): 22, Temp light failed"))return false;
	glUniformMatrix4fv(16, 1, GL_FALSE, &screenMat[0][0]);
	return true;
}


bool RenderEngine::Initialize(ShaderProgram * shaderP)
{
	if (!BufferManager::Initialize())return false;
	m_shaderProgramPtr = shaderP;

	if (!GetUniforms())return false;
	GameLogger::Log(LogMsgType::cProcess, "RenderEngine::Initialize() successful.");
	return true;
}

bool RenderEngine::Shutdown()
{
	if (!BufferManager::Shutdown()) return false;

	GameLogger::Log(LogMsgType::cProcess, "RenderEngine::Shutdown() successful.");
	return true;
}

bool RenderEngine::AddMesh(Mesh * mesh,GLuint shaderID, GLenum drawType, VertexFormats vertFormat)
{
	return BufferManager::AddMesh(mesh, shaderID, drawType, vertFormat);
}

bool RenderEngine::AddGraphicalObject(GraphicalObject * gob)
{
	return BufferManager::AddGraphicalObject(gob);
}

//TODO: make bool and crash
bool RenderEngine::Draw(glm::mat4 perspective, glm::mat4 camera, glm::mat4 option)
{
	
	GraphicalObject * currentGob = nullptr;// BufferManager::GetFirstGob();
	//int objectNum = 0;
	
	RenderInfo * gobRenderInfo = nullptr;
	//SetAttributes();
	BufferGroup * bGroup = nullptr;

	//while(BufferManager::)

	

	while (BufferManager::GetBufferGroup(bGroup)) {

		if (bGroup == nullptr) { printf("RenderEngine::Draw(): bGroup is null\n"); return false; }

		int shaderInd = bGroup->GetShaderIndex();

		//--------------------------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------------------------
		if (!ShaderManager::UseShader(shaderInd)) {
			printf("RenderEngine::Draw(): UseShader, shader [%d] does not exist\n", bGroup->GetShaderIndex());
			return false;
		}

		//if (shaderInd == 2)
		//{
		//	TextureManager::BindImage(0);
		//}

		//--------------------------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------------------------


		//GraphicalObject * bufferGroupGob = bGroup->GetFirstGob();
		//if (bufferGroupGob != nullptr) {//{ printf("RenderEngine::Draw(): bufferGroupGob is null\n");  return false; }
		RenderInfo * renderInfo = nullptr;// bufferGroupGob->GetRenderInfoPtr();
			//Refactor

			//SetAttributes(bGroup);

			while (bGroup->GetBufferInfoGob(currentGob))
			{
				if (currentGob != nullptr) {
					renderInfo = currentGob->GetRenderInfoPtr();
					glBindBuffer(GL_ARRAY_BUFFER, renderInfo->m_vertBufferID);
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderInfo->m_indBufferID);
					SetAttributes(&(renderInfo->m_vertexFormat), renderInfo->m_stride);

					//char * texInfo = TextureManager::GetData(0);

					while (currentGob != nullptr)
					{

						gobRenderInfo = currentGob->GetRenderInfoPtr();
						if (currentGob->GetEnabled()) {
							glm::mat4 screenMat;
							if (option != glm::mat4()) {
								screenMat =  option * (perspective * (camera * /*Set this to a parameter ->*/(currentGob->GetTranslateMatrix() * (currentGob->GetRotationMatrix() * currentGob->GetScaleMatrix()))));

							}
							else
							{
								screenMat = perspective * (camera * /*Set this to a parameter ->*/(currentGob->GetTranslateMatrix() * (currentGob->GetRotationMatrix() * currentGob->GetScaleMatrix())));

							}


							if (currentGob->m_drawCallback) {
								if (!currentGob->m_drawCallback(currentGob, screenMat)) return false;
							}
							else
							{
								if (shaderInd == 0) {
									SetUniformsShader0(currentGob, screenMat);
								}
								else if (shaderInd == 1) {
									if (!SetUniformsShader1(currentGob, screenMat)) return false;
								}
								else if (shaderInd == 2 || shaderInd == 3) {
									if (!SetUniformsShader2(currentGob, screenMat))return false;
									//return false;
								}
								else if (shaderInd == 4) {
									//glm::mat4 lightMat = perspective * (camera);

									if (!SetUniformsShader4(currentGob, screenMat)) return false;

								}
								else if (shaderInd == 5) {
									//glm::mat4 lightMat = perspective * (camera);

									if (!SetUniformsShader5(currentGob, screenMat)) return false;

								}
							}

							if (currentGob->GetRenderInfoPtr()->m_indexed) {

								DrawIndexedObject(currentGob);

							}
							else
							{

								DrawNonIndexedObject(currentGob);


							}
						}

						if (currentGob->m_drawCallback) {
							glDisable(GL_BLEND);
							glDisable(GL_CLIP_PLANE0);
						}
						currentGob = currentGob->GetNextObjectPtr();

						//objectNum++;
					}
				
			}
		}
	}
	
	return true;
}

bool RenderEngine::GetUniforms()
{
	m_shaderProgramPtr = ShaderManager::GetShaderProgram(0);
	m_positionAttrib = m_shaderProgramPtr->GetAttribLocation("vPosition");
	m_colorAttrib = 1;// m_shaderProgramPtr->GetAttribLocation("vColor");
	m_uniformLocCol	 =	m_shaderProgramPtr->GetUniformLocation("colorin");
	m_uniformLocMat4 =	m_shaderProgramPtr->GetUniformLocation("MAT");
	
	
	if (m_uniformLocCol < 0)
	{
		GameLogger::Log(LogMsgType::cFatalError, "CubeManager::GetUniforms(): m_uniformLocCol < 0.");
		return false;
	}
	if (m_uniformLocMat4 < 0)
	{
		GameLogger::Log(LogMsgType::cFatalError, "CubeManager::GetUniforms(): m_uniformLocMat4 < 0.");
		return false;
	}

	/*if (m_uniformLocCol < 0)
	{
		GameLogger::Log(LogMsgType::cFatalError, "CubeManager::GetUniforms(): m_uniformLocCol < 0.");
		return false;
	}
	if (m_uniformLocMat4 < 0)
	{
		GameLogger::Log(LogMsgType::cFatalError, "CubeManager::GetUniforms(): m_uniformLocMat4 < 0.");
		return false;
	}*/

	return true;
}

//Draw single object, can loop soon
//TODO: make drawall
//TODO: make seperate from gob
void RenderEngine::DrawIndexedObject(GraphicalObject * gob )
{

	//TODO: set attribs elsewhere

	RenderInfo * renderInfo = gob->GetRenderInfoPtr();
	

	//TODO: assign offsets elsewhere
	//static unsigned int colOffset = ColorVertex::GetColorOffset();
	//static unsigned int posOffset = ColorVertex::GetPositionOffset();
	//static GLint numPosits = 3;
	//static GLint numCols = 3;
	
		//glEnableVertexAttribArray(m_positionAttrib);
	//glEnableVertexAttribArray(m_colorAttrib);



	//glBindBuffer(GL_ARRAY_BUFFER, renderInfo->m_vertBufferID);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderInfo->m_indBufferID);
	
	//SetAttributes(gob, &(renderInfo->m_vertexFormat), renderInfo->m_stride);
	
	
	//glVertexAttribPointer(m_positionAttrib, numPosits, GL_FLOAT, GL_FALSE, renderInfo->m_stride, (void*)posOffset);
//	glVertexAttribPointer(m_colorAttrib, numCols, GL_FLOAT, GL_FALSE, renderInfo->m_stride, (void*)colOffset);



	//----------------------------HANDLE ELSEWHERE---------------------------
		//glUniform3fv(15, 1, (GLfloat*)gob->GetTint());
		//glUniformMatrix4fv(16, 1, GL_FALSE, &screenMat[0][0]);
	//-----------------------------------------------------------------------

	//GLuint * buffData = new GLuint[renderInfo->m_indexSizeBytes]{ 0 };
	//GLuint * buffDataPtr = buffData;
	//glGetBufferSubData(GL_ELEMENT_ARRAY_BUFFER, renderInfo->m_indexOffsetBytes, renderInfo->m_indexSizeBytes, buffData);
	//for (int i = 0; i < renderInfo->m_indexSizeBytes; i++)
	//{
	//	//printf("Element %d [%u]\n", i, *buffDataPtr);
	//	GameLogger::Log(LogMsgType::Debug, "Element %d: [%u]", i, *buffDataPtr);
	//	++buffDataPtr;
	//}
	//delete[] buffData;
	//GLfloat * buffData = new GLfloat[renderInfo->m_numVerts * 6]{ 0 };
	//GLfloat * buffDataPtr = buffData;
	//glGetBufferSubData(GL_ARRAY_BUFFER, renderInfo->m_vertOffset*sizeof(GLfloat)*6, renderInfo->m_numVerts * sizeof(GLfloat) * 6, buffData);
	//for (int i = 0; i < renderInfo->m_numVerts * 6; i++)
	//{
	//	//printf("Element %d [%u]\n", i, *buffDataPtr);
	//	GameLogger::Log(LogMsgType::Debug, "Element %d: [%f]", i, *buffDataPtr);
	//	++buffDataPtr;
	//}
	//delete[] buffData;

	glDrawElementsBaseVertex(renderInfo->m_draw_mode, renderInfo->m_numIndices, GetIndexType(renderInfo->m_isb),(void *)renderInfo->m_indexOffsetBytes,renderInfo->m_vertOffset);
}

void RenderEngine::DrawNonIndexedObject(GraphicalObject * gob)
{
	//static unsigned int colOffset = ColorVertex::GetColorOffset();
	//static unsigned int posOffset = ColorVertex::GetPositionOffset();
	//static GLint numPosits = ColorVertex::GetNumPositions();
	//static GLint numCols = ColorVertex::GetNumCols();

	//RenderInfo * renderInfo = gob->GetRenderInfoPtr();
	//glm::mat4 screenMat = perspective * (camera * (gob->GetTranslateMatrix() * (gob->GetRotationMatrix() * gob->GetScaleMatrix())));
	
	//TODO:MAGIC NUMBERS -- remove

	//glBindBuffer(GL_ARRAY_BUFFER, renderInfo->m_vertBufferID);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderInfo->m_indBufferID);
	//glEnableVertexAttribArray(m_positionAttrib);
	//glEnableVertexAttribArray(m_colorAttrib);
	
	//SetAttributes(gob, &(renderInfo->m_vertexFormat), renderInfo->m_stride);

	RenderInfo * renderInfo = gob->GetRenderInfoPtr();
	

	//glUniform3fv(15, 1, (GLfloat*)gob->GetTint());
	//glUniformMatrix4fv(16, 1, GL_FALSE, &screenMat[0][0]);


	glDrawArrays(renderInfo->m_draw_mode,renderInfo->m_vertOffset, renderInfo->m_numVerts);
	//glDrawElementsBaseVertex(gob->GetDrawType(), renderInfo->m_numIndices, GL_UNSIGNED_INT, (void *)renderInfo->m_indexOffsetBytes, renderInfo->m_vertOffset);

}





bool RenderEngine::SetAttributes(VertexFormats * vertType, GLsizei stride)
{


	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	// pre-define some constants values to make the function calls slightly more readable
	const GLint     positionQuantity = 3;  // positions need 3 floats, XYZ
	const GLint     colorQuantity = 3;  // colors    need 3 floats, RGB -- TODO: Handle 4 floats RGBA ??
	const GLint     textureQuantity = 2;  // textures  need 2 floats, UV
	const GLint     normalQuantity = 3;  // normals   need 3 floats, XYZ



										 //const GLsizei   vertexStride = stride;  // example: 36 for position, color, normal = (3 + 3 + 3) * sizeof(float)
	GLuint         attribIndex = 0; // the current attrib

	GLsizei        currentOffset = 0; // NOTE: YOU MUST USE THE CORRECT VALUE HERE ...!?!?!?!?!?!,

	GLsizei        formatOffset = 0; // an offset into the current vertex format, always starts at 0



									 // NOTE: attribIndex and formatOffset are modified by SetAttrib()!!!
	if ((int)(*vertType) & (int)VertexFormats::HasPosition) SetAttrib(attribIndex, positionQuantity, stride, currentOffset, formatOffset);
	if ((int)(*vertType) & (int)VertexFormats::HasColor)
	{
		SetAttrib(attribIndex, colorQuantity, stride, currentOffset, formatOffset);
	}
	if ((int)(*vertType) & (int)VertexFormats::HasTexture)
	{
		SetAttrib(attribIndex, textureQuantity, stride, currentOffset, formatOffset);
	}
	if ((int)(*vertType) & (int)VertexFormats::HasNormal)   SetAttrib(attribIndex, normalQuantity, stride, currentOffset, formatOffset);

	//currentOffset += gob->GetNumVerts() * gob->GetStride; // you will need to update your own structure with this new offset

	// Other code goes here
	return true;
}

//bool RenderEngine::SetAttributes(BufferGroup * bGroup)
//{
//	
//	VertexFormats * vertType = bGroup->GetVertexFormat();
//	GLsizei stride = (GLsizei)VertStride::GetSize(*vertType);
//	//bGroup->
//	glDisableVertexAttribArray(0);
//	glDisableVertexAttribArray(1);
//	glDisableVertexAttribArray(2);
//	glDisableVertexAttribArray(3);
//	// pre-define some constants values to make the function calls slightly more readable
//	const GLint     positionQuantity = 3;  // positions need 3 floats, XYZ
//	const GLint     colorQuantity = 3;  // colors    need 3 floats, RGB -- TODO: Handle 4 floats RGBA ??
//	const GLint     textureQuantity = 2;  // textures  need 2 floats, UV
//	const GLint     normalQuantity = 3;  // normals   need 3 floats, XYZ
//
//
//
//										 //const GLsizei   vertexStride = stride;  // example: 36 for position, color, normal = (3 + 3 + 3) * sizeof(float)
//	GLuint         attribIndex = 0; // the current attrib
//
//	GLsizei        currentOffset = 0; // NOTE: YOU MUST USE THE CORRECT VALUE HERE ...!?!?!?!?!?!, 0 IS PROBABLY ONLY CORRECT FOR A NEW BUFFER
//
//	GLsizei        formatOffset = 0; // an offset into the current vertex format, always starts at 0
//
//
//
//									 // NOTE: attribIndex and formatOffset are modified by SetAttrib()!!!
//	if ((int)(*vertType) & (int)VertexFormats::HasPosition) SetAttrib(attribIndex, positionQuantity, stride, currentOffset, formatOffset);
//	if ((int)(*vertType) & (int)VertexFormats::HasColor)    SetAttrib(attribIndex, colorQuantity, stride, currentOffset, formatOffset);
//	if ((int)(*vertType) & (int)VertexFormats::HasTexture)  SetAttrib(attribIndex, textureQuantity, stride, currentOffset, formatOffset);
//	if ((int)(*vertType) & (int)VertexFormats::HasNormal)   SetAttrib(attribIndex, normalQuantity, stride, currentOffset, formatOffset);
//
//	//currentOffset += gob->GetNumVerts() * gob->GetStride; // you will need to update your own structure with this new offset
//
//	// Other code goes here
//	return true;
//}

void RenderEngine::SetAttrib(GLuint& attribIndex, GLint quantity, GLsizei vertexStride, GLsizei currentOffset, GLsizei & formatOffset)
{
	// pre-define some constants values to make the function calls slightly more readable
	const GLboolean isNormalized = GL_FALSE;
	const GLenum    dataType = GL_FLOAT;

	glEnableVertexAttribArray(attribIndex);
	glVertexAttribPointer(attribIndex, quantity, dataType, isNormalized, vertexStride, (void*)(currentOffset + formatOffset));
	formatOffset += quantity * sizeof(dataType); // move over the data to the next (example: move over the position to get to the color)
	++attribIndex;                                // move to the next attrib
}