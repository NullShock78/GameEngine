#ifndef  CAMERA_H
#define CAMERA_H

//Kyle St.Amant
//7/9/2016
//description here

#pragma warning(push)  //Save state																												 
#pragma warning(disable:4201) //disable 
#include "mat4x4.hpp"
#include "gtc/matrix_transform.hpp"	
#pragma warning(pop)

using glm::vec3;

class Camera
{
	


public:
	

	glm::mat4 GetWorldToViewMatrix();
	glm::mat4 GetReflectionToViewMatrix(glm::vec3 otherPos = glm::vec3(0,0,0));


	void MouseRotate(int dx, int dy);

	void SetXSpeed(float speed);
	void SetYSpeed(float speed);
	void SetZSpeed(float speed);
	void IncrementSpeed(float speed);
	//void SetViewDir(glm::vec3)
	void SetPos(glm::vec3 pos);
	void SetSensitivity(float sensitivity);
	void RotateVec(float x, float y);
	void MoveUp(float dt);
	void MoveDown(float dt);
	void MoveLeft(float dt);
	void MoveRight(float dt);
	void MoveForward(float dt);
	void MoveBack(float dt);
	void WalkForward(float dt);
	void WalkBack(float dt);
	void LookAt(glm::vec3 point);
	void PrintCameraInfo();

	void Reflect(glm::vec3 otherCameraDir, bool negative = true);

	glm::vec3 GetPosition();

	glm::mat4 GetRotationMatrix();


	//void LookLeft(float dt);
	//void LookRight(float dt);

	bool Initialize(float sensitivity = 0.25f,vec3 position = vec3(0, 0, 0),
		vec3 viewDir = vec3(0, 0, -1.0f),
		vec3 up = vec3(0, 1.0f, 0),
		float x_speed = 10.0f,
		float y_speed = 10.0f,
		float z_speed = 10.0f);

	bool Shutdown();
	//Is normalized;
	glm::vec3 GetLookVec();
private:
	//glm::mat4 m_translate;

	glm::vec3 m_position;//m_eye;
	glm::vec3 m_viewDir;//m_center;view dir
	glm::vec3 m_up;
	glm::vec3 m_right;
	glm::vec3 m_forward;

	//Will be replaced with normal?
	glm::vec3 m_initialDir;

	glm::mat4 m_rotationMatrix;
	glm::mat4 m_translateMatrix;

	int m_yaw;
	int m_pitch;

	float m_xSpeed;
	float m_ySpeed;
	float m_zSpeed;

	float m_sensitivity;
};

#endif //def CAMERA_H


