#include "CameraComponent.h"
#include "SpatialComponent.h"
#include "MouseComponent.h"
#include "KeyboardComponent.h"
//#include "GraphicalObjectComponent.h"


void CameraComponent::UpdateRotation()
{
/*
	AddPitch(-m_mouse->GetDY(m_mouseSide)*(int)m_sensitivity);// *(int)m_sensitivity);
	AddYaw(-m_mouse->GetDX(m_mouseSide)*(int)m_sensitivity);// );

	static const glm::vec3 up = V_UP;//glm::vec3(0, 1.0f, 0);
	static const glm::vec3 right = V_RIGHT;// glm::vec3(1.0f, 0, 0);
	static const glm::vec3 forward = V_FORWARD;// glm::vec3(0, 0, -1.0f);

	


	glm::mat4 rotMat = glm::rotate(glm::mat4(), glm::radians(static_cast<float>(m_yaw)), up);
	glm::vec3 tempForward = glm::vec3(rotMat * glm::vec4(forward, 1.0f));
	glm::vec3 tempLook = tempForward;

	m_right = glm::normalize(glm::cross(tempForward, up));
	rotMat = glm::rotate(rotMat, glm::radians(static_cast<float>(m_pitch)), m_right);
	tempLook = glm::vec3(rotMat * glm::vec4(tempLook, 1.0f));

	m_forward = tempForward;// glm::normalize(glm::cross(up, m_right));

	glm::vec3 z = glm::normalize(tempLook);
	glm::vec3 x = glm::normalize(glm::cross(up, z));
	glm::vec3 y = glm::cross(z, x);
	glm::mat4 newMat = glm::mat4(x.x, x.y, x.z, 0.0f, y.x, y.y, y.z, 0.0f, z.x, z.y, z.z, 0.0f, 0, 0, 0, 1);


	m_viewDir = z;

	m_right = x;
	*/

	AddPitch(-m_mouse->GetDY(m_mouseSide)*(int)m_sensitivity);
	AddYaw(-m_mouse->GetDX(m_mouseSide)*(int)m_sensitivity);

	static const glm::vec3 up = V_UP;//glm::vec3(0, 1.0f, 0);
	static const glm::vec3 right = V_RIGHT;// glm::vec3(1.0f, 0, 0);
	static const glm::vec3 forward = V_FORWARD;// glm::vec3(0, 0, -1.0f);



	glm::mat4 rotMat = glm::rotate(glm::mat4(), glm::radians(static_cast<float>(m_yaw)), up);
	glm::vec3 tempForward = glm::vec3(rotMat * glm::vec4(forward, 1.0f));
	glm::vec3 tempLook = tempForward;

	m_right = glm::normalize(glm::cross(tempForward, up));
	rotMat = glm::rotate(rotMat, glm::radians(static_cast<float>(m_pitch)), m_right);
	tempLook = glm::vec3(rotMat * glm::vec4(tempLook, 1.0f));

	m_forward = tempForward;// glm::normalize(glm::cross(up, m_right));

	glm::vec3 z = glm::normalize(tempLook);
	glm::vec3 x = glm::normalize(glm::cross(up, z));
	glm::vec3 y = glm::cross(z, x);
	glm::mat4 newMat = glm::mat4(x.x, x.y, x.z, 0.0f, y.x, y.y, y.z, 0.0f, z.x, z.y, z.z, 0.0f, 0, 0, 0, 1);


	m_viewDir = z;

	m_right = x;

	//if (m_lockObjRotate)
	//{
		//m_spatial->SetYaw(m_yaw);
		//m_spatial->SetPitch(-m_pitch);

		//m_spatial->SetRightVec(x);
		//m_spatial->SetLookVec(-z);
		//m_spatial->SetUpVec(y);
		//m_spatial->SetForwardVec(glm::normalize(glm::cross(up, m_spatial->GetRightVec())));
		//m_spatial->SetRotate(newMat);
	//}
	//m_up = m_spatial->GetUpVec();
}

void CameraComponent::AddYaw(int a)
{
	m_yaw += a;
}

void CameraComponent::CenterPosAndVec()
{
	m_offset = 0;
	m_yaw = m_spatial->GetYaw();
	m_pitch = m_spatial->GetPitch();

}

void CameraComponent::CenterViewYaw()
{
	m_yaw = m_spatial->GetYaw()/2;
	m_forward = m_spatial->GetForwardVec();
	m_right = m_spatial->GetRightVec();
	//m_viewDir = m_spatial->GetLookVec();
	m_rotationMatrix = m_spatial->GetRotate();
}

void CameraComponent::AddPitch(int a)
{
	m_pitch += a;
	
		if (m_pitch > 89)
		{
			m_pitch = 89;
		}
		else if (m_pitch < -89)
		{
			m_pitch = -89;
		}
	
}

bool CameraComponent::Initialize( glm::vec3 viewDir, float offset, float sensitivity,glm::vec3 offsetVec)
{
	//Todo: log
	m_spatial = m_owner->GetComponentByType<SpatialComponent>();
	if (!m_spatial) return false;
	m_mouse = GetSiblingComponent<MouseComponent>();
	if (m_mouse == nullptr) return false;
	m_keyboard = GetSiblingComponent<KeyboardComponent>();
	if (m_keyboard == nullptr) return false;

	if(!m_keyboard->AddKey('Z')) return false;
	
	//m_gobComp = GetSiblingComponent<GraphicalObjectComponent>();
	//if (m_gobComp == nullptr) return false;

	m_yaw = 180; //Turn it around

	m_offset = offset;
	m_offsetVec = offsetVec;
	m_viewDir = glm::normalize(viewDir);
	m_rotationMatrix = glm::mat4();

	m_right = glm::cross(m_viewDir, m_up);
	m_forward = glm::cross(m_up, m_right);


	//m_xSpeed = x_speed;
	//m_ySpeed = y_speed;
	//m_zSpeed = z_speed;

	m_pitch = 0;
	m_yaw   = 0;
	m_sensitivity = sensitivity;

	m_up = glm::vec3(0, 1.0f, 0);

	return true;//m_camera.Initialize(1.0f, glm::vec3(), glm::vec3(0, 0, 1.0f));
}


glm::mat4 CameraComponent::GetWorldToViewMatrix()
{
	//return glm::lookAt(m_position, m_position + m_viewDir, m_up);

	glm::vec3 pos = m_spatial->GetPos() + m_offsetVec + (m_viewDir*m_offset);
	return glm::lookAt(pos, pos + m_viewDir, m_up);
	//return m_camera.GetWorldToViewMatrix();
}

glm::mat4 CameraComponent::GetRotationMatrix()
{
	return m_rotationMatrix;
}

void CameraComponent::SetSensitivity(float sensitivity)
{
	m_sensitivity = sensitivity;
}


void CameraComponent::PrintCameraInfo()
{
	GameLogger::Log(LogMsgType::ConsoleOnly, "---------|Camera Info|---------------------\n\tCamera Pos         = (%f, %f, %f)\n\tCamera viewDir vec = (%f, %f, %f)",
		m_spatial->GetPos().x, m_spatial->GetPos().y, m_spatial->GetPos().z, m_viewDir.x, m_viewDir.y, m_viewDir.z);
	GameLogger::Log(LogMsgType::ConsoleOnly, "-------------------------------------------");

}

void CameraComponent::SetRight(glm::vec3 vec)
{
	m_right = vec;
}

void CameraComponent::SetMouseButton(bool right)
{
	m_mouseSide = right;
}



void CameraComponent::SetUpVec(glm::vec3 vec)
{
	m_up = vec;
}

void CameraComponent::SetOffset(float offset)
{
	m_offset = offset;
}

glm::vec3 CameraComponent::GetViewDir()
{
	return m_viewDir;
}

bool CameraComponent::Update(float /*dt*/)
{
	if (m_keyboard->IsKeyDown('Z'))
	{
		CenterViewYaw();
	}
	//CenterViewYaw();
	UpdateRotation();

	
	//printf("delta: %d\n", m_mouse->GetDeltaWheel());
	m_offset += m_mouse->GetDeltaWheel();
	if (m_offset > 0) m_offset = 0;

	m_pos = m_spatial->GetPos() + m_offsetVec + (m_viewDir*m_offset);

	return true;
}

glm::vec3 CameraComponent::GetPos()
{
	return m_pos;
}

const float * CameraComponent::GetPosPtr()
{
	return &m_pos[0];
}

int CameraComponent::GetYaw()
{
	return m_yaw;
}

int CameraComponent::GetPitch()
{
	return m_pitch;
}

