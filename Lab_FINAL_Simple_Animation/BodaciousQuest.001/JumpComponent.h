#ifndef  JUMP_COMPONENT_H
#define JUMP_COMPONENT_H

//Kyle St.Amant
//8/21/2016
//description here

#include "Component.h"
class GravityComponent;
class MovementComponent;
class KeyboardComponent;
class JumpComponent : public Component
{

private:
	MovementComponent * m_movement;
	GravityComponent  * m_gravity;
	KeyboardComponent * m_keyboard;
	bool m_canJump{ false };
	float m_jumpSpeed{ 10.0f };
public:

	bool Initialize();
	bool Update(float dt);

};

#endif //def JUMP_COMPONENT_H


