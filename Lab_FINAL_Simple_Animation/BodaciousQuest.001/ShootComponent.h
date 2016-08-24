#ifndef  SHOOT_COMPONENT_H
#define SHOOT_COMPONENT_H

//Kyle St.Amant
//8/20/2016
//description here
#include "Component.h"
#include "CollisionTester.h"


class CameraComponent;
class KeyboardComponent;
class ShootComponent : public Component
{
private:
	CollisionTester		m_collision;
	CameraComponent		* m_camera;
	KeyboardComponent	* m_keyboard;
	GraphicalObject	* m_entityToLaunch;
	float m_distance{ 0.0f };
public:
	bool Initialize();
	bool Update(float dt);

	bool SetAmmo(GraphicalObject * entity);
};

#endif //def SHOOT_COMPONENT_H


