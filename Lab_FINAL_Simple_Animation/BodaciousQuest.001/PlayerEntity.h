#ifndef  PLAYER_ENTITY_H
#define PLAYER_ENTITY_H

//Kyle St.Amant
//8/16/2016

#include "Entity.h"
#include "Component.h"
#include "SpatialComponent.h"
#include "CameraComponent.h"
#include "MovementComponent.h"
#include "MouseComponent.h"
#include "KeyboardComponent.h"
#include "GravityComponent.h"
#include "GraphicalObjectComponent.h"
#include "CollisionTester.h"
#include "JumpComponent.h"
#include "ShootComponent.h"
#include "MyWindow.h"

class PlayerEntity : public Entity
{
private:
	GraphicalObjectComponent m_gobcomp;
	SpatialComponent m_spatial;
	CameraComponent m_cam;
	MovementComponent m_movement;
	MouseComponent m_mouse;
	KeyboardComponent m_keyboard;
	GravityComponent m_gravity;
	JumpComponent m_jump;
	ShootComponent m_phasor;
public:
	CollisionTester m_tester;

public:
	//bool Update(float dt);
	bool Initialize(glm::vec3 pos = glm::vec3(), glm::vec3 offset = glm::vec3(0,0,0) );
	glm::mat4 GetCameraMatrix();
	GraphicalObject * GetGob();
	glm::vec3 GetPosition();
	glm::vec3 GetCamPosition();
	glm::vec3 GetLookVec();
	bool Update(float dt);
	const float * GetCamPos();

	void SetScale(float scale);
	//glm::vec3 GetCamPosition();
	//bool AddCollisionObj(GraphicalObject * gob);
	
	void SetAmmo(GraphicalObject * gob);

	//bool AddCollisionObj(GraphicalObject * gob);

	//bool AddToMouseCallback(MyWindow * window);
};

#endif //def PLAYER_ENTITY_H


