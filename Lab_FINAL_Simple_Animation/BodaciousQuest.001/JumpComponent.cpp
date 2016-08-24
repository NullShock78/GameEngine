#include "JumpComponent.h"
#include "KeyboardComponent.h"
#include "MovementComponent.h"
#include "GravityComponent.h"
#include <Windows.h>
bool JumpComponent::Initialize()
{

	m_movement = GetSiblingComponent<MovementComponent>();
	if (!m_movement) return false;
	m_keyboard = GetSiblingComponent<KeyboardComponent>();
	if (!m_keyboard) return false;
	m_gravity = GetSiblingComponent<GravityComponent>();
	if (!m_gravity) return false;

	if (!m_keyboard->AddKey(VK_SPACE)) return false;


	return true;
}

bool JumpComponent::Update(float /*dt*/)
{
	m_canJump = m_gravity->OnGround();

	
		if (m_keyboard->IsKeyDown(VK_SPACE)) {
			if (m_canJump)
			{
				m_movement->SetGravityVel(m_jumpSpeed);
			}
		}
	
	return true;
}
