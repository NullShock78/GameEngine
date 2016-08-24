#include "MovementComponent.h"
#include "SpatialComponent.h"
#include "GraphicalObjectComponent.h"
#include "CameraComponent.h"
#include "KeyboardComponent.h"
#include "MouseComponent.h"
#include <windows.h>

//float MovementComponent::m_dx;
//float MovementComponent::m_dy;
void MovementComponent::ApplyMovement(float dt)
{
	glm::vec3 nextPos = m_spatial->GetPos();

	m_velocity = glm::vec3(0.0f, m_velocity.y, 0.0f);

	if (m_forward)
	{ 
		if (m_lockObjRotate) {
			m_velocity -= m_spatial->GetLookVec()  * m_speedZ * m_speedFactor;
		}
		else
		{
			m_velocity -= m_spatial->GetForwardVec()  * m_speedZ * m_speedFactor;
		}
	}
	if (m_back) { 
		if (m_lockObjRotate) {
			m_velocity += m_spatial->GetLookVec()  * m_speedZ * m_speedFactor;
		}
		else
		{
			m_velocity += m_spatial->GetForwardVec()  * m_speedZ * m_speedFactor;
		}
	}
	

	if (m_right) {
	//	glm::vec3 r = m_spatial->GetRightVec();

		if (m_lockObjRotate) {
			m_velocity -= m_spatial->GetRightVec() * m_speedX * m_speedFactor;
		}
		else
		{
			AddYaw(int(-300.0f*dt));
		}
	}
	if (m_left) {
		if (m_lockObjRotate) {
			m_velocity += m_spatial->GetRightVec() * m_speedX * m_speedFactor;
		}
		else
		{
			AddYaw(int(300.0f*dt));
		}
	}


	if (m_up)		m_velocity += glm::vec3(0, 1.0f, 0)	* m_speedY * m_speedFactor;
	if (m_down)		m_velocity -= glm::vec3(0, 1.0f, 0)	* m_speedY * m_speedFactor;


	

	glm::vec3 tempVel = glm::vec3(m_velocity.x,0.0f, m_velocity.z);
	
	

	//if(m_velocity.x != 0 &&   tempVel = glm::normalize(tempVel) * m_speedX;

	m_velocity = glm::vec3(tempVel.x,m_gravityVel, tempVel.z);
	m_velocity.x *= 0.91f;
	m_velocity.z *= 0.91f;

	m_velocity.x = (m_velocity.x > m_speedX) ? m_speedX : m_velocity.x;
	m_velocity.z = (m_velocity.z > m_speedZ) ? m_speedZ : m_velocity.z;

	m_spatial->SetPos(nextPos + (m_velocity * dt));
	m_gobComponent->SetPos(nextPos + (m_velocity * dt));
	
}

bool MovementComponent::UpdateRotation()
{
	//static const glm::vec3 up = glm::vec3(0, 1.0f, 0);
	////m_yaw += dx;
	////m_pitch += dy;
	//int dx = m_mouse->GetDX();
	//int dy = m_mouse->GetDY();
	//if (dx != 0) {
	//	m_spatial->SetLookVec(glm::vec3(glm::rotate(glm::mat4(), -static_cast<float>(dx) * m_rotationSensitivity, up) * glm::vec4(m_spatial->GetLookVec(), 1.0f)));
	//	m_spatial->SetForwardVec(glm::vec3(glm::rotate(glm::mat4(), -static_cast<float>(dx) * m_rotationSensitivity, up) * glm::vec4(m_spatial->GetForwardVec(), 1.0f)));
	//	m_spatial->SetRightVec(glm::cross(m_spatial->GetForwardVec(), up));
	//}
	////Clamp camera up/down rotation so you don't spazz when you look straight up.
	//if (m_spatial->GetPitch() < -89) {
	//	m_spatial->SetPitch(-89);
	//}
	//else if (m_spatial->GetPitch() > 89) {
	//	m_spatial->SetPitch(89);
	//}
	//else if(dy != 0)
	//{ 
	//	m_spatial->SetLookVec(glm::vec3(glm::rotate(glm::mat4(), -static_cast<float>(dy) * m_rotationSensitivity, m_spatial->GetRightVec()) * glm::vec4(m_spatial->GetLookVec(), 1.0f)));
	//}

	//if (!m_lockObjRotate) {
	//	AddPitch(-m_mouse->GetDY() * (int)m_rotationSensitivity);
	//	AddYaw(-m_mouse->GetDX() * (int)m_rotationSensitivity);
	//}
	//	static const glm::vec3 up = V_UP;//glm::vec3(0, 1.0f, 0);
	//	static const glm::vec3 right = V_RIGHT;//glm::vec3(1.0f, 0, 0);
	//	static const glm::vec3 forward = V_FORWARD; //glm::vec3(0, 0, 1.0f);

	//	glm::mat4 rotMat = glm::rotate(glm::mat4(), glm::radians(static_cast<float>(m_spatial->GetYaw())), up);
	//	glm::vec3 tempForward = glm::vec3(rotMat * glm::vec4(forward, 1.0f));
	//	glm::vec3 tempLook = tempForward;

	//	m_spatial->SetRightVec(glm::cross(tempForward, up));
	//	rotMat = glm::rotate(rotMat, glm::radians(static_cast<float>(m_spatial->GetPitch())), m_spatial->GetRightVec());
	//	tempLook = glm::vec3(rotMat * glm::vec4(tempLook, 1.0f));

	//	m_spatial->SetLookVec(tempLook);

	//	m_spatial->SetRotate(rotMat);

	static const glm::vec3 up = V_UP;//glm::vec3(0, 1.0f, 0);
	static const glm::vec3 right = V_RIGHT;// glm::vec3(1.0f, 0, 0);
	static const glm::vec3 forward = V_FORWARD;// glm::vec3(0, 0, 1.0f);
		
	if (!m_lockObjRotate) {
		m_dy = m_mouse->GetDY(true);
		AddPitch(m_dy);

		m_dx = m_mouse->GetDX(true);
		AddYaw(-m_dx);
	}
	else
	{
		m_spatial->SetYaw(m_cameraComponent->GetYaw());
		m_spatial->SetPitch(-m_cameraComponent->GetPitch());
	}
		glm::mat4 rotMat = glm::rotate(glm::mat4(), glm::radians(static_cast<float>(m_spatial->GetYaw())), up);
		glm::vec3 tempForward = glm::vec3(rotMat * glm::vec4(forward, 1.0f));
		glm::vec3 tempLook = tempForward;
		glm::vec3 tempRight = glm::normalize(glm::cross(up,tempForward));
		m_spatial->SetRightVec(tempRight);
		//glm::vec3 tempUp = up;
		if (m_lockObjRotate) {
			rotMat = glm::rotate(rotMat, glm::radians(static_cast<float>(m_spatial->GetPitch())), tempRight);
			tempLook = glm::vec3(rotMat * glm::vec4(tempLook, 1.0f));
		}

		tempRight = glm::normalize(glm::cross(up, tempLook));

		glm::vec3 z = glm::normalize(tempLook);
		glm::vec3 x = glm::normalize(glm::cross(up, z));
		glm::vec3 y = glm::cross(z, x);
		glm::mat4 newMat =  glm::mat4(x.x, x.y, x.z, 0.0f, y.x, y.y, y.z, 0.0f, z.x, z.y, z.z, 0.0f, 0, 0, 0, 1);
		m_spatial->SetRightVec(x);
		m_spatial->SetLookVec(-z);
		m_spatial->SetUpVec(y);

		m_spatial->SetForwardVec(glm::normalize(glm::cross(up, m_spatial->GetRightVec())));
		m_spatial->SetRotate(newMat);

		
		//m_gobComponent->SetRotationMat(m_spatial->GetRotate());
		
		
/*
	if (m_flying) {
		m_dy = m_mouse->GetDY();
		AddPitch(-m_dy * (int)m_rotationSensitivity);
	}
	
	m_dx = m_mouse->GetDX();
	AddYaw(-m_dx * (int)m_rotationSensitivity);

	if (m_mouse->GetDX()* (int)m_rotationSensitivity != 0)
	{
		printf("yaw		move: %d\n", m_mouse->GetDX()* (int)m_rotationSensitivity);
		printf("spacial  yaw: %d\n", m_spatial->GetYaw());

	}
	
	//if (m_mouse->GetDX() != 0)
	//{
	//	printf("yaw move: %d\n", m_mouse->GetDX());
	//}

	glm::vec3 tempLook		= forward;
	glm::vec3 tempRight		= right;
	glm::vec3 tempForward	= forward;

	glm::mat4 rotMat = glm::rotate(glm::mat4(), glm::radians(static_cast<float>(m_spatial->GetYaw()/2)), up);
	
	tempForward = glm::vec3(rotMat * glm::vec4(forward, 1.0f));
	tempLook	= tempForward;
	tempRight	= glm::normalize(glm::cross(tempForward, up));
	rotMat		= glm::rotate(rotMat, glm::radians(static_cast<float>(m_spatial->GetPitch())), tempRight);
	tempLook	= glm::vec3(rotMat * glm::vec4(tempLook, 1.0f));
	m_spatial->SetForwardVec(tempForward);

	glm::vec3 z = glm::normalize(tempLook);
	glm::vec3 x = glm::normalize(glm::cross(up, z));
	glm::vec3 y = glm::cross(z, x);

	m_spatial->SetRotate(glm::mat4(x.x, x.y, x.z, 0.0f, y.x, y.y, y.z, 0.0f, z.x, z.y, z.z, 0.0f, 0, 0, 0, 1));

	
	m_spatial->SetRightVec(x);
	m_spatial->SetUpVec(y);
	m_spatial->SetLookVec(z);*/

	//m_gobComponent->SetRotationMat(m_spatial->GetRotate());
	return true;
}

bool MovementComponent::UpdateCamera()
{
	//m_cameraComponent->RotateVec(m_dx)

	return true;
}

void MovementComponent::UpdateKeystrokes()
{

	if (!m_freeze_forward) {
		if (m_keyboard->IsKeyDown('W'))
		{
			m_forward = true;
		}
	}
	if (!m_freeze_left) {
		if (m_keyboard->IsKeyDown('A'))
		{
			m_left = true;
		}
	}
	if (!m_freeze_back) {
		if (m_keyboard->IsKeyDown('S'))
		{
			m_back = true;
		}
	}
	if (!m_freeze_right) {

		if (m_keyboard->IsKeyDown('D'))
		{
			m_right = true;
		}
	}
	if (!m_freeze_up) {

		if (m_keyboard->IsKeyDown('R'))
		{
			m_up = true;
		}
	}
	if (!m_freeze_down) {
		if (m_keyboard->IsKeyDown(VK_SHIFT) || m_keyboard->IsKeyDown('F'))
		{
			m_down = true;
		}
	}

	if (m_forward || m_back || m_left || m_right || m_down || m_up)
	{
		m_moving = true;
	}

	if (m_keyboard->KeyWasPressed('B'))
	{
		m_cameraComponent->PrintCameraInfo();
	}
}



bool MovementComponent::Initialize()
{
	m_gobComponent = GetSiblingComponent<GraphicalObjectComponent>();
	if (m_gobComponent == nullptr) return false;
	m_spatial = GetSiblingComponent<SpatialComponent>();
	if (m_spatial == nullptr) return false;
	m_keyboard = GetSiblingComponent<KeyboardComponent>();
	if (m_keyboard == nullptr) return false;
	m_cameraComponent = GetSiblingComponent<CameraComponent>();
	if (m_cameraComponent == nullptr) return false;
	m_mouse = GetSiblingComponent<MouseComponent>();
	if (m_mouse == nullptr) return false;
	if (!m_keyboard->AddKey('W')) return false;
	if (!m_keyboard->AddKey('A')) return false;
	if (!m_keyboard->AddKey('S')) return false;
	if (!m_keyboard->AddKey('D')) return false;
	if (!m_keyboard->AddKey('R')) return false;
	if (!m_keyboard->AddKey('F')) return false;
	if (!m_keyboard->AddKey(VK_LEFT)) return false;
	if (!m_keyboard->AddKey(VK_RIGHT)) return false;

	if (!m_keyboard->AddKey(VK_SHIFT)) return false;


	//m_flying
	if (!m_keyboard->AddToggle(VK_UP, &m_flying, true)) return false;
	if (!m_keyboard->AddToggle(VK_DOWN, &m_lockObjRotate, false)) return false;

	if (!m_keyboard->AddKey('B')) return false;

	m_velocity = glm::vec3(0, 0, 0);
	m_lockObjRotate = false;

	return true;
}

bool MovementComponent::Update(float dt)
{

	UpdateKeystrokes();

	
	//AddYaw((-m_mouse->GetDX() * m_rotationSensitivity)  * dt);
	//AddPitch((-m_mouse->GetDY() * m_rotationSensitivity) * dt);
	ApplyMovement(dt);
	UpdateRotation();
	
	
	
	

	m_moving	= false;			
	m_forward	= false;
	m_back		= false;
	m_left		= false;
	m_right		= false;
	m_up		= false;
	m_down		= false;

	return true;
}

//void MovementComponent::LookAt(glm::vec3 point)
//{
//	
//	static glm::vec3 up = glm::vec3(0, 1.0f, 0);
//
//	glm::vec3 z = glm::normalize(point - m_spatial->GetPos());
//	glm::vec3 x = glm::normalize(glm::cross(up, z));
//	glm::vec3 y = glm::cross(z, x);
//	glm::mat4 newMat =  glm::mat4(x.x, x.y, x.z, 0.0f, y.x, y.y, y.z, 0.0f, z.x, z.y, z.z, 0.0f, 0, 0, 0, 1);
//	m_gobComponent->SetRotationMat(newMat);
//	//m_rotationMat = newMat;// glm::rotate(glm::mat4(), glm::radians(-180.0f), z);// *m_scaleMat;
//
//	
//}/*glm::translate(glm::mat4(), -z)**/

void MovementComponent::AddYaw(int a)
{
	m_spatial->AddYaw(a);
	
}

void MovementComponent::AddPitch(int a)
{
	m_spatial->AddPitch(a);
}

void MovementComponent::SetRotationSensitivity(float sensitivity)
{
	m_rotationSensitivity = sensitivity;
}

void MovementComponent::MoveForward()
{
	m_forward = true;
	//m_spatial->SetPosX(m_spatial->GetPos() )
}

void MovementComponent::MoveBackwards()
{

	m_forward = true;
}

void MovementComponent::MoveRight()
{
	m_right = true;
}

void MovementComponent::MoveLeft()
{
	m_left = true;
}

void MovementComponent::MoveUp()
{
	m_up = true;
}

void MovementComponent::MoveDown()
{
	m_down = true;
}

void MovementComponent::SetGravityVel(float vel)
{
	m_gravityVel = vel;
}

float MovementComponent::GetGravityVel()
{
	return m_gravityVel;
}

void MovementComponent::AddVelocity(glm::vec3 vel)
{
	m_velocity += vel;
}

void MovementComponent::LockObj(bool lock)
{
	m_lockObjRotate = lock;
}

void MovementComponent::FreezeMovementForward(bool lock)
{
	m_freeze_forward = lock;
}

void MovementComponent::FreezeMovementBackwards(bool lock)
{
	m_freeze_back = lock;
}


void MovementComponent::FreezeMovementRight(bool lock)
{
	m_freeze_right = lock;
}

void MovementComponent::FreezeMovementLeft(bool lock)
{
	m_freeze_left = lock;
}

void MovementComponent::FreezeMovementUp(bool lock)
{
	m_freeze_up = lock;
}

void MovementComponent::FreezeMovementDown(bool lock)
{
	m_freeze_down = lock;
}
