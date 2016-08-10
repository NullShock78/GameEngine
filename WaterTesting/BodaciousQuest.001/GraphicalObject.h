#ifndef  GRAPHICAL_OBJECT_H
#define GRAPHICAL_OBJECT_H

//Kyle St.Amant
//7/6/2016
//description here

#pragma warning(push)  //Save state																												 
#pragma warning(disable:4201) //disable warnings	
#include "GL\glew.h"	
#include "vec3.hpp"																														 
#include "mat4x4.hpp"		
#include "gtc/matrix_transform.hpp"		
#pragma warning(pop) //return to previous warning state			

#include "Mesh.h"

#include <functional>
//#include "RenderInfo.h"




class RenderInfo;

class GraphicalObject
{
private:
	RenderInfo		* m_renderInfo{ nullptr };
	GraphicalObject * m_next{ nullptr };

	Mesh * m_mesh;

	glm::mat4 m_scaleMat;
	glm::mat4 m_translateMat;
	glm::mat4 m_rotationMat;
	glm::mat4 m_transformMat;

	glm::vec3 m_rotationAxis{ glm::vec3(0,0,0) };
	GLfloat m_rotateAngle{ 0.0f };
	GLfloat m_yaw;
	GLfloat m_pitch;
	GLfloat m_roll;
	//glm::vec3 m_tint;
	float m_tint[3]{ 0.0f };

	GLuint m_textureID{ 0 };
	GLuint m_normalID { 0 };
	GLfloat m_rotateSpeed;
	GLenum m_drawType{ GL_TRIANGLES };
	bool ownsData{ false };
	glm::vec3 m_pos{ glm::vec3(0,0,0) };
	glm::vec3 m_up{ glm::vec3(0,-1.0f,0) };
	glm::vec3 m_dir{ glm::vec3(0,0.0f,1.0f) };

	GraphicalObject * m_light1{ nullptr };

public:

	std::function <bool(GraphicalObject *, glm::mat4)> m_drawCallback;
	GraphicalObject * GetLight();

	~GraphicalObject();
	//RenderInfo * renderInfo;
	void SetNextObjectPtr(GraphicalObject * next);
	GraphicalObject * GetNextObjectPtr();
	RenderInfo * GetRenderInfoPtr();
	void SetDrawType(GLenum drawType);
	void SetHasData(bool hasData = false);
	void SetMesh(Mesh * mesh);
	void SetScaleMatrix(glm::mat4 scale_mat);
	void SetTranslateMatrix(glm::mat4 translate_mat);
	void SetRotationMatrix(glm::mat4 rotation_mat);
	void SetRotationAxis(glm::vec3 axisVec);
	void SetRotateAngle(GLfloat angle);
	GLfloat * GetPosX();

	void SetLight(GraphicalObject * gob);
	
	

	void SetTexture(GLuint id);
	GLuint GetTexture();
	void SetNormalTexture(GLuint id);
	GLuint GetNormalTexture();
	//Use degrees
	void Rotate(GLfloat angle);
	glm::mat4 * GetTransformMat();
	void SetScale(glm::vec3 scale);
	void SetScale(float x, float y, float z);
	void SetScale(float scale);
	//TODO: remove
	void SetAlignedToAxisAndRotation(GLfloat angle);
	void BakeTransformMatrix();

	void LookAt(glm::vec3 point);
	void Billboard(glm::vec3 point);
	//void LookAt(glm::vec3 point);
	void SetPos(glm::vec3 pos);
	glm::vec3 GetPos();
	GLenum GetDrawType();
	GLsizei GetMeshVertSizeBytes();
	GLsizei GetMeshIndexSizeBytes();
	GLsizei GetNumVerts();
	GLsizei GetNumIndices();
	void SetTint(glm::vec3 color);
	void SetTint(float r, float g, float b);
	void * GetVertexDataStart();
	void * GetIndexDataStart();
	GLfloat GetRotateAngle();
	glm::vec3 GetRotateAxis();
	GLfloat GetRotateSpeed();
	void * GetTint();
	glm::vec3 GetVecTint();
	glm::mat4 GetScaleMatrix();
	glm::mat4 GetTranslateMatrix();
	glm::mat4 GetRotationMatrix();

};

#endif //def GRAPHICAL_OBJECT_H


