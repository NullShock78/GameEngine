#include "ShootComponent.h"
#include "CameraComponent.h"
#include "KeyboardComponent.h"
#include "GraphicalObject.h"
bool ShootComponent::Initialize()
{
	m_camera = GetSiblingComponent<CameraComponent>();
	if (!m_camera) return false;
	m_keyboard = GetSiblingComponent<KeyboardComponent>();
	if (!m_keyboard) return false;

	if (!m_keyboard->AddKey('.')) return false;
	if (!m_keyboard->AddKey('>')) return false;

	return true;
}

bool ShootComponent::Update(float /*dt*/)
{

	
	if (m_keyboard->KeyWasPressed('.') || m_keyboard->KeyWasPressed('>'))
	{
		//printf("Pew\n");
		m_distance = m_collision.FindWall(m_camera->GetPos(), m_camera->GetViewDir(), true);
		if (m_entityToLaunch) m_entityToLaunch->SetPos(m_collision.GetIntersection());
	}

	return true;
}

bool ShootComponent::SetAmmo(GraphicalObject * entity)
{
	m_entityToLaunch = entity;

	return true;
}
