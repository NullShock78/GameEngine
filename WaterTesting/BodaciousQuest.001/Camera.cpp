#include "Camera.h"
#include "GameLogger.h"


bool Camera::Initialize(float sensitivity, vec3 position,
	vec3 viewDir, vec3 up, 
	float x_speed, float y_speed, float z_speed)
{
	m_position = position;
	m_viewDir = glm::normalize(viewDir);
	m_up = up;

	m_rotationMatrix = glm::mat4();

	m_right = glm::cross(m_viewDir, m_up);
	m_forward = glm::cross(m_up, m_right);

	m_initialDir = viewDir;

	m_xSpeed = x_speed;
	m_ySpeed = y_speed;
	m_zSpeed = z_speed;

	m_pitch = 0;
	m_yaw = 0;
	m_sensitivity = sensitivity;

	GameLogger::Log(LogMsgType::cProcess, "Camera::Initialize() successful.");
	return true;
}

bool Camera::Shutdown()
{

	GameLogger::Log(LogMsgType::cProcess, "Camera::Shutdown() successful.");
	return true;
}

glm::vec3 Camera::GetLookVec()
{
	return m_viewDir;
}



glm::mat4 Camera::GetWorldToViewMatrix()
{
	return glm::lookAt(m_position, m_position + m_viewDir, m_up);
}

glm::mat4 Camera::GetReflectionToViewMatrix(glm::vec3 /*otherPos*/)
{
	glm::mat4 temp = glm::scale(GetWorldToViewMatrix(), glm::vec3(-1.0f, 1.0f, 1.0f));
	
	//glm::distance(otherPos, m_position);

	//temp = temp * glm::translate(glm::mat4(),  glm::vec3(0,0,0 ));
	return  temp;
}

//glm::mat4 Camera::GetWorldToViewMatrix2()
//{
//	return glm::lookAt(m_position, m_position + m_viewDir, m_up);
//}

//----------------------------MOUSE ROTATE---------------------------
void Camera::MouseRotate(int dx, int dy)
{
	//Y-axis, ie right/left
	m_yaw += dx;
	//X-axis, ie up/down
	m_pitch += dy;

	//printf("%d, %d\n", m_yaw, m_pitch);
	
	//m_right = glm::vec3(glm::rotate(glm::mat4(), -static_cast<float>(dx) * m_sensitivity, m_right) * glm::vec4(m_right, 1.0f));
	

	//m_rotationMatrix = glm::rotate(glm::mat4(), static_cast<float>(m_yaw)*m_sensitivity, m_up);
	m_viewDir = glm::vec3(glm::rotate(glm::mat4(), -static_cast<float>(dx) * m_sensitivity, m_up) * glm::vec4(m_viewDir, 1.0f));
	m_forward = glm::vec3(glm::rotate(glm::mat4(), -static_cast<float>(dx) * m_sensitivity, m_up) * glm::vec4(m_forward, 1.0f));
	m_right = glm::cross(m_forward, m_up);
	//Clamp camera up/down rotation so you don't spazz when you look straight up.
	



	if (m_pitch < -89) {
		m_pitch = -89;
	}
	else if (m_pitch > 89) {
		m_pitch = 89;
	}
	else
	{
		
		//m_rotationMatrix = glm::rotate(glm::mat4(), -static_cast<float>(m_pitch)*m_sensitivity, m_right);
		m_viewDir = glm::vec3(glm::rotate(glm::mat4(), -static_cast<float>(dy) * m_sensitivity, m_right) * glm::vec4(m_viewDir, 1.0f));

		
	}
	

}//------------------------------------------------------------------

void Camera::SetXSpeed(float speed)
{
	m_xSpeed = speed;
}

void Camera::SetYSpeed(float speed)
{
	m_ySpeed = speed;
}

void Camera::SetZSpeed(float speed)
{
	m_zSpeed = speed;
}

void Camera::IncrementSpeed(float speed)
{
	m_xSpeed += speed;
	m_ySpeed += speed;
	m_zSpeed += speed;

	//Temp 
	if (m_xSpeed < 5.0f) {
		m_xSpeed = 5.0f;
		m_ySpeed = 5.0f;
		m_zSpeed = 5.0f;
	}

	if (m_xSpeed > 60.0f) {
		m_xSpeed = 60.0f;
		m_ySpeed = 60.0f;
		m_zSpeed = 60.0f;
	}

}

void Camera::SetPos(glm::vec3 pos)
{
	m_position = pos;
}

void Camera::SetSensitivity(float sensitivity)
{
	m_sensitivity = sensitivity;
}

void Camera::RotateVec(float x, float y)
{
	m_viewDir = glm::vec3(glm::rotate(glm::mat4(), x, m_up) * glm::vec4(m_viewDir, 1.0f));

	m_viewDir = glm::vec3(glm::rotate(glm::mat4(), y, m_right) * glm::vec4(m_viewDir, 1.0f));

}


void Camera::MoveUp(float dt)
{
	m_position += m_up * (m_ySpeed * dt);
}

void Camera::MoveDown(float dt)
{
	m_position -= m_up * (m_ySpeed * dt);
}

void Camera::MoveLeft(float dt)
{
	m_position -= m_right * (m_xSpeed * dt);
}

void Camera::MoveRight(float dt)
{
	m_position += m_right * (m_xSpeed * dt);
}

void Camera::MoveForward(float dt)
{
	m_position += m_viewDir * (m_zSpeed * dt);
}

void Camera::MoveBack(float dt)
{
	m_position -= m_viewDir * (m_zSpeed * dt);
}


void Camera::WalkForward(float dt)
{
	m_position += m_forward * (m_zSpeed * dt);
}

void Camera::WalkBack(float dt)
{
	m_position -= m_forward * (m_zSpeed * dt);
}

void Camera::LookAt(glm::vec3 point)
{

	//DOESN'T WORK
	//static glm::vec3 up = glm::vec3(0, 1.0f, 0);

	//::vec3 z = glm::normalize(point - m_position);
	//glm::vec3 x = glm::normalize(glm::cross(up, z));
	//glm::vec3 y = glm::cross(z, x);
	//glm::mat4 newMat = glm::translate(glm::mat4(), -z)* glm::mat4(x.x, x.y, x.z, 0.0f, y.x, y.y, y.z, 0.0f, z.x, z.y, z.z, 0.0f, 0, 0, 0, 1);
	m_viewDir = -glm::normalize(  m_position - point);
	
	//m_rotationMat = newMat;// glm::rotate(glm::mat4(), glm::radians(-180.0f), z);// *m_scaleMat;


}


void Camera::PrintCameraInfo()
{
	GameLogger::Log(LogMsgType::ConsoleOnly, "---------|Camera Info|---------------------\n\tCamera Pos         = (%f, %f, %f)\n\tCamera viewDir vec = (%f, %f, %f)",
		m_position.x,m_position.y,m_position.z, m_viewDir.x,m_viewDir.y,m_viewDir.z);
	GameLogger::Log(LogMsgType::ConsoleOnly, "-------------------------------------------");

}

void Camera::Reflect(glm::vec3 otherCameraDir, bool /*negative*/)
{

	//glm::vec3 oDir = (negative) ? otherCameraDir : -otherCameraDir;
	//m_viewDir = glm::vec3(glm::rotate(glm::mat4(), glm::radians(180.0f), m_initialDir) * glm::vec4(oDir,1.0f)) ;

	static glm::vec3 up = glm::vec3(0, 1.0f, 0);
	 
	//glm::vec3 z = -glm::normalize(otherCameraDir - m_position);
	//glm::vec3 x = glm::normalize(glm::cross(up, z));
	//glm::vec3 y = glm::cross(z, x);
	//glm::mat4 newMat = glm::translate(glm::mat4(), -z)* glm::mat4(x.x, x.y, x.z, 0.0f, y.x, y.y, y.z, 0.0f, z.x, z.y, z.z, 0.0f, 0, 0, 0, 1);

	m_viewDir = glm::normalize(glm::reflect(glm::normalize(otherCameraDir - m_position), glm::vec3(0, 1.0f, 0)));   //glm::vec3(glm::rotate(glm::mat4(), glm::radians(180.0f),m_initialDir) *-glm::vec4(m_position - otherCameraDir, 1.0f)); //glm::reflect(glm::normalize(   m_position - otherCameraDir), m_initialDir);
}


glm::vec3 Camera::GetPosition()
{
	return m_position;
}

glm::mat4 Camera::GetRotationMatrix()
{
	return m_rotationMatrix;
}



