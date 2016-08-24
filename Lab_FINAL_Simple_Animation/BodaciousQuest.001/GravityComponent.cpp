#include "GravityComponent.h"
#include "MovementComponent.h"
#include "SpatialComponent.h"
bool GravityComponent::Update(float dt)
{
	m_onGround = true;

	m_groundDistance = m_collision.FindWall(m_spatial->GetPos() + glm::vec3(0, 1.0f, 0), glm::vec3(0, -1.0f, 0), true);
	if (m_spatial->GetPos().y < m_collision.GetIntersection().y)
	{
		m_spatial->SetPos(m_collision.GetIntersection());
	}
	
	
	if (m_groundDistance > 1.1f) m_onGround = false;
	
	if (!m_onGround) {
		m_movement->SetGravityVel(m_movement->GetGravityVel() - (m_gravityAccel * dt));
	}
	else
	{
		m_movement->SetGravityVel(0.0f);
	}
	return true;
}

bool GravityComponent::Initialize()
{
	m_movement = GetSiblingComponent<MovementComponent>();
	if (!m_movement) return false;

	m_spatial = GetSiblingComponent<SpatialComponent>();
	if (!m_spatial) return false;
	m_gravityAccel = 9.8f;
	return true;
}

bool GravityComponent::OnGround()
{
	return m_onGround;
}

void GravityComponent::SetGravity(float gravity)
{
	m_gravityAccel = gravity;
}
