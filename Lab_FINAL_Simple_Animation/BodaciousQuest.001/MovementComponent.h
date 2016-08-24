#ifndef  MOVEMENT_COMPONENT_H
#define MOVEMENT_COMPONENT_H

//Kyle St.Amant
//8/15/2016
//description here

#include "Component.h"
#pragma warning(push)  //Save state																												 
#pragma warning(disable:4201) //disable warnings	
#include "gtc\matrix_transform.hpp"																											 
#pragma warning(pop) 


class SpatialComponent;
class GraphicalObjectComponent;
class CameraComponent;
class KeyboardComponent;
class MouseComponent;
class MovementComponent : public Component
{
private:
	SpatialComponent * m_spatial{ nullptr };
	GraphicalObjectComponent * m_gobComponent{ nullptr };
	CameraComponent * m_cameraComponent{ nullptr };
	KeyboardComponent * m_keyboard{ nullptr };
	MouseComponent * m_mouse{ nullptr };
	int m_dx;
	int m_dy;

	glm::vec3 m_velocity{ glm::vec3(0,0,0) };
	float m_drag{ 0.0f };

	float m_speedFactor{ 1.0f };
	float m_speedX{ 10.0f };
	float m_speedY{ 10.0f };
	float m_speedZ{ 10.0f };
	float m_rotationSensitivity{ 1.0f };

	bool m_flying{ false };


	bool m_moving{ false };
	
	bool m_forward{ false };
	bool m_back{ false };
	bool m_left{ false };
	bool m_right{ false };
	bool m_up{ false };
	bool m_down{ false };

	bool m_freeze_forward{ false };
	bool m_freeze_back{ false };
	bool m_freeze_left{ false };
	bool m_freeze_right{ false };
	bool m_freeze_up{ false };
	bool m_freeze_down{ false };

	void ApplyMovement(float dt);
	bool UpdateRotation();
	bool UpdateCamera();

	bool m_lockObjRotate{ false };

	void UpdateKeystrokes();
	float m_gravityVel{ 0.0f };

	bool m_lockCamBehindObj{ true };

public:

	bool Initialize();
	bool Update(float dt);
	//void LookAt(glm::vec3 point);
	void AddYaw(int a);
	void AddPitch(int a);
	glm::vec3 GetVel();
	void SetVel(glm::vec3 vel);
	void SetRotationSensitivity(float sensitivity);
	void MoveForward();
	void MoveBackwards();
	void MoveRight();
	void MoveLeft();
	void MoveUp();
	void MoveDown();

	void SetGravityVel(float vel);
	float GetGravityVel();
	void AddVelocity(glm::vec3 vel);
	void LockObj(bool lock = true);

	void FreezeMovementForward(bool lock = true);
	void FreezeMovementBackwards(bool lock = true);
	void FreezeMovementRight(bool lock = true);
	void FreezeMovementLeft(bool lock = true);
	void FreezeMovementUp(bool lock = true);
	void FreezeMovementDown(bool lock = true);


};

#endif //def MOVEMENT_COMPONENT_H


