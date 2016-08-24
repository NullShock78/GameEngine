#ifndef  GRAVITY_COMPONENT_H
#define GRAVITY_COMPONENT_H

//Kyle St.Amant
//8/21/2016
//description here
#include "CollisionTester.h"
#include "Component.h"
class MovementComponent;
class SpatialComponent;
class GravityComponent : public Component
{
private:
	CollisionTester m_collision;
	MovementComponent * m_movement;
	SpatialComponent * m_spatial;
	bool m_onGround{ true };

	float m_groundDistance;

	float m_gravityAccel{ 9.8f };
public:
	bool Update(float dt);
	bool Initialize();
	bool OnGround();
	void SetGravity(float gravity);
};

#endif //def GRAVITY_COMPONENT_H


