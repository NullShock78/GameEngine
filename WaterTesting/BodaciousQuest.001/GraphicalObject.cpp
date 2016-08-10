#include "GraphicalObject.h"

#pragma warning(push)  //Save state																												 
#pragma warning(disable:4201) //disable warnings	
#include "gtc/matrix_transform.hpp"																											 
#pragma warning(pop) //return to previous warning state			


GraphicalObject * GraphicalObject::GetLight()
{
	return m_light1;
}

GraphicalObject::~GraphicalObject()
{
	if (ownsData)
	{
		delete m_mesh;
		//GameLogger::Log(LogMsgType::cDebug, "~GraphicalObject(): deleted mesh successfully.");
	}

}

void GraphicalObject::SetNextObjectPtr(GraphicalObject * next)
{
		m_next = next;
}

GraphicalObject * GraphicalObject::GetNextObjectPtr()
{
	return m_next;
}

RenderInfo * GraphicalObject::GetRenderInfoPtr()
{
	return m_mesh->GetRenderInfo();
}

void GraphicalObject::SetDrawType(GLenum drawType)
{
	m_drawType = drawType;

}

void GraphicalObject::SetHasData(bool hasData)
{
	ownsData = hasData;
}

void GraphicalObject::SetMesh(Mesh * mesh)
{ 
	m_mesh = mesh; 
}

void GraphicalObject::SetScaleMatrix(glm::mat4 scale_mat) 
{ 
	m_scaleMat = scale_mat; 
}

void GraphicalObject::SetTranslateMatrix(glm::mat4 translate_mat) 
{ 
	m_translateMat = translate_mat; 
	
}

void GraphicalObject::SetRotationMatrix(glm::mat4 rotation_mat) 
{ 
	m_rotationMat = rotation_mat; 
}

void GraphicalObject::SetRotationAxis(glm::vec3 axisVec) 
{ 
	m_rotationAxis = axisVec; 
}



void GraphicalObject::SetRotateAngle(GLfloat angle)
{
	m_rotateAngle = angle;
}
GLfloat * GraphicalObject::GetPosX()
{
	return &m_pos.r;
}

void GraphicalObject::SetLight(GraphicalObject * gob)
{
	m_light1 = gob;
}

void GraphicalObject::SetTexture(GLuint id)
{
	m_textureID = id;
}
GLuint GraphicalObject::GetTexture()
{
	return m_textureID;
}
void GraphicalObject::SetNormalTexture(GLuint id)
{
	m_normalID = id;
}
GLuint GraphicalObject::GetNormalTexture()
{
	return m_normalID;
}
//Assumes normalized Axis
void  GraphicalObject::Rotate(GLfloat angle)
{
	//m_rotateAngle += angle;
	//m_yaw += m_rotationAxis.y * angle;
	//m_pitch += m_rotationAxis.x * angle;
	//m_roll += m_rotationAxis.z * angle;
	//m_rotationMat = glm::rotate(glm::mat4(), glm::radians(m_rotateAngle), m_rotationAxis);
	//m_rotationMat = glm::rotate(glm::mat4(), glm::radians(m_rotateAngle), m_rotationAxis);
	
	m_rotationMat =  glm::rotate(m_rotationMat, glm::radians(angle), m_rotationAxis);

	m_up = glm::vec3(glm::rotate(m_rotationMat, glm::radians(angle), m_rotationAxis) * glm::vec4(m_up,1.0f)) ;
	//m_rotationAxis = glm::vec3(glm::rotate(glm::mat4(),angle,m_rotationAxis) * (glm::vec4(m_rotationAxis, 1.0f)));
	//m_rotationMat = glm::rotate(glm::mat4(), glm::radians(angle), m_rotationAxis - glm::vec3(m_pitch, m_yaw, m_roll));
	//m_rotationAxis -= glm::vec3(m_pitch, m_yaw, m_roll);
}


//Use degrees
void  GraphicalObject::SetAlignedToAxisAndRotation(GLfloat angle)
{
	//m_rotateAngle += angle;
	//m_rotationMat = glm::rotate(glm::mat4(), glm::radians(m_rotateAngle), m_rotationAxis);
	
	m_rotationMat = glm::rotate(glm::mat4(), glm::radians(angle), m_rotationAxis);
}

//"Bake it, Luigi!" -- Applies all matrices
void GraphicalObject::BakeTransformMatrix()
{
	m_transformMat = (m_translateMat * (m_rotationMat* m_scaleMat));
}

void GraphicalObject::LookAt(glm::vec3 point)
{
	//glm::vec3 pos = glm::vec3(0, 0, 0);
	//pos = glm::vec3(m_translateMat * glm::vec4(pos, 0.0f));
	//m_rotationMat = (glm::lookAt(point,  pos , glm::vec3(0, 1.0f, 0.0f)))*m_scaleMat;// glm::vec3(0, 1.0f, 0)
	
	static glm::vec3 up = glm::vec3(0, 1.0f, 0);

	glm::vec3 z = glm::normalize( point - m_pos);
	glm::vec3 x = glm::normalize(glm::cross(up, z));
	glm::vec3 y = glm::cross(z , x);
	glm::mat4 newMat = /*glm::translate(glm::mat4(), -z)**/ glm::mat4(x.x, x.y, x.z, 0.0f, y.x, y.y, y.z, 0.0f, z.x, z.y, z.z, 0.0f, 0, 0, 0, 1);
	m_rotationMat = newMat;// glm::rotate(glm::mat4(), glm::radians(-180.0f), z);// *m_scaleMat;
	

}

void GraphicalObject::Billboard(glm::vec3 point)
{
	static glm::vec3 up = glm::vec3(0, 1.0f, 0);
	glm::vec3 newPoint = glm::vec3(point.x, m_pos.y, point.z);
	glm::vec3 z = glm::normalize(newPoint - m_pos);
	glm::vec3 x = glm::normalize(glm::cross(up, z));
	glm::vec3 y = glm::cross(z, x);
	glm::mat4 newMat = /*glm::translate(glm::mat4(), -z)**/ glm::mat4(x.x, x.y, x.z, 0.0f, y.x, y.y, y.z, 0.0f, z.x, z.y, z.z, 0.0f, 0, 0, 0, 1);
	m_rotationMat = newMat;// glm::rotate(glm::mat4(), glm::radians(-180.0f), z);// *m_scaleMat;

}

void GraphicalObject::SetPos(glm::vec3 pos)
{
	m_translateMat = glm::translate(glm::mat4(), pos);
	m_pos = pos;
}

glm::vec3 GraphicalObject::GetPos()
{
	return m_pos;
}

glm::mat4 * GraphicalObject::GetTransformMat()
{
	BakeTransformMatrix();
	return &m_transformMat;//(m_translateMat * (m_rotationMat * m_scaleMat));;
}

void GraphicalObject::SetScale(glm::vec3 scale)
{
	m_scaleMat = glm::scale(glm::mat4(), scale);
}

void GraphicalObject::SetScale(float x, float y, float z)
{
	SetScale(glm::vec3(x, y, z));
}

void GraphicalObject::SetScale(float scale)
{
	SetScale(glm::vec3(scale, scale, scale));
}



GLenum GraphicalObject::GetDrawType()
{
	return m_drawType;
}

GLsizei  GraphicalObject::GetMeshVertSizeBytes()
{ 
	return m_mesh->GetVertSizeInBytes(); 
}
GLsizei  GraphicalObject::GetMeshIndexSizeBytes() 
{ 
	return m_mesh->GetIndexSizeInBytes(); 
}
GLsizei GraphicalObject::GetNumVerts()
{
	return m_mesh->GetNumVerts();
}
GLsizei GraphicalObject::GetNumIndices()
{
	return m_mesh->GetNumIndices();
}

void  GraphicalObject::SetTint(glm::vec3 color) 
{ 
	//m_tint = color; 
	SetTint(color.r, color.g, color.b);

}

void GraphicalObject::SetTint(float r, float g, float b)
{
	m_tint[0] = r;
	m_tint[1] = g;
	m_tint[2] = b;
}

void *  GraphicalObject::GetVertexDataStart() 
{ 
	return m_mesh->GetVertexDataStart(); 
}
void *  GraphicalObject::GetIndexDataStart()
{ 
	return m_mesh->GetIndexDataStart(); 
}
GLfloat  GraphicalObject::GetRotateAngle() 
{ 
	return m_rotateAngle; 
}
glm::vec3  GraphicalObject::GetRotateAxis() 
{ 
	return m_rotationAxis; 
}
GLfloat  GraphicalObject::GetRotateSpeed() 
{ 
	return m_rotateSpeed; 
}
void * GraphicalObject::GetTint()
{
	return &m_tint[0];
}

glm::vec3 GraphicalObject::GetVecTint()
{
	return glm::vec3(m_tint[0], m_tint[1], m_tint[2]);
}

glm::mat4  GraphicalObject::GetScaleMatrix() 
{ 
	return m_scaleMat; 
}
glm::mat4  GraphicalObject::GetTranslateMatrix() 
{ 
	return m_translateMat; 
}
glm::mat4  GraphicalObject::GetRotationMatrix() 
{ 
	return m_rotationMat; 
}

