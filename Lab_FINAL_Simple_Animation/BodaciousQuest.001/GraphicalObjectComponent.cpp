#include "GraphicalObjectComponent.h"
#include "SpatialComponent.h"

void GraphicalObjectComponent::SetRotationMat(glm::mat4 mat)
{
	m_gob.SetRotationMatrix(mat);
}

void GraphicalObjectComponent::SetTranslateMat(glm::mat4 mat)
{
	m_gob.SetTranslateMatrix(mat);
}


//for debugging
glm::mat4 GraphicalObjectComponent::GetRotationMatrix()
{
	return m_gob.GetRotationMatrix();
}

//for debugging
glm::mat4 GraphicalObjectComponent::GetScaleMatrix()
{
	return m_gob.GetScaleMatrix();
}

//for debugging
glm::mat4 GraphicalObjectComponent::GetTranslateMatrix()
{
	return m_gob.GetTranslateMatrix();
}

GraphicalObject * GraphicalObjectComponent::GetGob()
{
	return &m_gob;
}

bool GraphicalObjectComponent::Update(float dt)
{

	m_gob.SetTranslateMatrix(m_spatial->GetTranslate());
	m_gob.SetRotationMatrix(m_spatial->GetRotate());
	m_gob.SetScaleMatrix(m_spatial->GetScale());


	return true;
}

bool GraphicalObjectComponent::Initialize()
{
	m_spatial = GetSiblingComponent<SpatialComponent>();
	if (m_spatial == nullptr) return false;
	m_gob.SetRotationMatrix(m_spatial->GetRotate());
	return true;
}

void GraphicalObjectComponent::LookAt(glm::vec3 forward)
{
	m_gob.LookAtVec(forward);
}

void GraphicalObjectComponent::SetPos(glm::vec3 pos)
{
	m_gob.SetPos(pos);
}

void GraphicalObjectComponent::SetScale(float scale)
{
	m_gob.SetScale(scale);
}
