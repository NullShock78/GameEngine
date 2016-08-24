#ifndef  CAMERA_COMPONENT_H
#define CAMERA_COMPONENT_H

//Kyle St.Amant
//8/16/2016

#include "Camera.h"
#include "Component.h"
class SpatialComponent;
class MouseComponent;
class KeyboardComponent;

//class GraphicalObjectComponent;
class CameraComponent : public Component
{

protected:
	SpatialComponent * m_spatial{ nullptr };
	MouseComponent * m_mouse{ nullptr };
	KeyboardComponent * m_keyboard;// { nullptr };
	//GraphicalObjectComponent * m_gobComp{ nullptr };
	glm::mat4 m_rotationMatrix{ glm::mat4() };
	//glm::mat4 m_translateMatrix;

	glm::vec3 m_pos{ glm::vec3() };

	//Camera m_camera;
	float m_offset{ 0.0f };
	//glm::vec3 m_offsetVec{ glm::vec3(0,0,0) };
	float m_sensitivity{ 1.0f };
	glm::vec3 m_viewDir;//m_center;view dir
	glm::vec3 m_up{ glm::vec3(0,-1.0f,0) };
	glm::vec3 m_right{ glm::vec3(1.0f,0,0) };
	glm::vec3 m_forward{ glm::vec3(0,0,-1.0f) };
	int m_yaw{ 180 };
	int m_pitch{ 0 };

	//True = right
	bool m_mouseSide{ true }; 
	glm::vec3 m_offsetVec{ glm::vec3(0,0,0) };

	void UpdateRotation();
	void AddYaw(int a);
	void CenterPosAndVec();
	void AddPitch(int a);

	bool m_lockObjRotate{ true };
public :
	bool Initialize(glm::vec3 viewDir, float offset, float sensitivity, glm::vec3 offsetVec = glm::vec3(0,0,0));
	glm::mat4 GetWorldToViewMatrix();
	void CenterViewYaw();

	glm::mat4 GetRotationMatrix();

	void SetSensitivity(float sensitivity);

	void PrintCameraInfo();
	void SetRight(glm::vec3 vec);
	void SetMouseButton(bool right);
	void SetUpVec(glm::vec3 vec);
	void SetOffset(float offset);
	glm::vec3 GetViewDir();
	bool Update(float dt);
	glm::vec3 GetPos();
	const float * GetPosPtr();
	int GetYaw();
	int GetPitch();
};

#endif //def CAMERA_COMPONENT_H



