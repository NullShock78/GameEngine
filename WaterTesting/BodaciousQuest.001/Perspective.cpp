#include "Perspective.h"


#pragma warning(push)																											 
#pragma warning(disable:4201)
#include "gtc/matrix_transform.hpp"
#pragma warning(pop)

void Perspective::SetPerspective(float fov, float aspect, float zNear, float zFar)
{
	m_fov = glm::radians(fov);
	m_aspect = aspect;
	m_zNear = zNear;
	m_zFar = zFar;

	m_perspective = glm::perspective(m_fov, m_aspect, m_zNear, m_zFar);
}

glm::mat4 Perspective::GetPerspective()
{
	return m_perspective;
}


void Perspective::SetAspect(float aspect)
{
	m_aspect = aspect;
	m_perspective = glm::perspective(m_fov, m_aspect, m_zNear, m_zFar);
}
