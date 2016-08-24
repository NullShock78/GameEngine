#include "SpatialComponent.h"
#pragma warning(push)  //Save state																												 
#pragma warning(disable:4201) //disable warnings	
#include "gtc\matrix_transform.hpp"																											 
#pragma warning(pop) 


void SpatialComponent::SetYaw(int angle)
{
	m_yaw = angle;

}

void SpatialComponent::SetPitch(int angle)
{
	m_pitch = angle;
}

void SpatialComponent::SetRoll(int angle)
{
	m_roll = angle;
}

void SpatialComponent::AddYaw(int angle)
{
	m_yaw += angle;
	if (m_yaw >= 360)
	{
		m_yaw -= 360;
	}
	else if (m_yaw <= -360)
	{
		m_yaw += 360;
	}
}

void SpatialComponent::AddPitch(int angle)
{
	m_pitch += angle;
	if (m_constrainPitch) {
		if (m_pitch > 89)
		{
			m_pitch =  89;
		}
		else if (m_pitch < -89)
		{
			m_pitch = -89;
		}
	}
	else
	{
		if (m_pitch >= 360)
		{
			m_pitch -= 360;
		}
		else if (m_pitch <= -360)
		{
			m_pitch += 360;
		}
	}
}

void SpatialComponent::AddRoll(int angle)
{
	m_roll += angle;
	if (m_roll >= 360)
	{
		m_roll -= 360;
	}
	else if (m_roll <= -360)
	{
		m_roll += 360;
	}

}

void SpatialComponent::SetPos(glm::vec3 pos)
{
	m_pos = pos;
	
}

void SpatialComponent::SetPosX(float amount)
{
	m_pos.x = amount;
}
void SpatialComponent::SetPosY(float amount)
{
	m_pos.y = amount;
}
void SpatialComponent::SetPosZ(float amount)
{
	m_pos.z = amount;
}

glm::vec3 SpatialComponent::GetPos()
{
	return m_pos;
}

void SpatialComponent::ConstrainPitch(bool constrain)
{
	m_constrainPitch = constrain;
}

int SpatialComponent::GetYaw()
{
	return m_yaw;
}

int SpatialComponent::GetPitch()
{
	return m_pitch;
}

int SpatialComponent::GetRoll()
{
	return m_roll;
}

glm::mat4 SpatialComponent::GetTranslate()
{
	return glm::translate(glm::mat4(), m_pos);
}

glm::mat4 SpatialComponent::GetRotate()
{
	return m_rotate;
}

glm::mat4 SpatialComponent::GetScale()
{
	return m_scale;
}

void SpatialComponent::SetRotate(glm::mat4 mat)
{
	m_rotate = mat;
}

void SpatialComponent::SetScale(glm::mat4 mat)
{
	m_scale = mat;
}

void SpatialComponent::SetScale(float scale)
{
	m_scale = glm::scale(glm::mat4(), glm::vec3(scale, scale, scale));
}

glm::vec3 SpatialComponent::GetLookVec()
{
	return m_lookVec;
}

glm::vec3 SpatialComponent::GetRightVec()
{
	return m_right;
}

glm::vec3 SpatialComponent::GetForwardVec()
{
	return m_forward;
}

glm::vec3 SpatialComponent::GetUpVec()
{
	return m_up;
}

void SpatialComponent::SetLookVec(glm::vec3 vec)
{
	m_lookVec = vec;
}

void SpatialComponent::SetForwardVec(glm::vec3 vec)
{
	m_forward = vec;
}

void SpatialComponent::SetRightVec(glm::vec3 vec)
{
	m_right = vec;
}

void SpatialComponent::SetUpVec(glm::vec3 vec)
{
	m_up = vec;
}

//bool SpatialComponent::UpdateRotations(float dt)
//{
//	glm::mat4 rotMat = glm::rotate(glm::mat4(), glm::radians(static_cast<float>(m_yaw)), V_UP);
//	glm::vec3 tempForward = glm::vec3(rotMat * glm::vec4(V_FORWARD, 1.0f));
//	glm::vec3 tempLook = tempForward;
//	glm::vec3 tempRight = glm::normalize(glm::cross(V_UP, tempForward));
//	SetRightVec(tempRight);
//	//glm::vec3 tempUp = up;
//	
//	rotMat = glm::rotate(rotMat, glm::radians(static_cast<float>(m_spatial->GetPitch())), tempRight);
//	tempLook = glm::vec3(rotMat * glm::vec4(tempLook, 1.0f));
//	
//	tempRight = glm::normalize(glm::cross(up, tempLook));
//
//	glm::vec3 z = glm::normalize(tempLook);
//	glm::vec3 x = glm::normalize(glm::cross(up, z));
//	glm::vec3 y = glm::cross(z, x);
//	glm::mat4 newMat = glm::mat4(x.x, x.y, x.z, 0.0f, y.x, y.y, y.z, 0.0f, z.x, z.y, z.z, 0.0f, 0, 0, 0, 1);
//	m_spatial->SetRightVec(x);
//	m_spatial->SetLookVec(-z);
//	m_spatial->SetUpVec(y);
//
//	m_spatial->SetForwardVec(glm::normalize(glm::cross(up, m_spatial->GetRightVec())));
//	m_spatial->SetRotate(newMat);
//
//	return true;
//}
//
