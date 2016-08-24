#ifndef  SPACIAL_COMPONENT_H
#define SPACIAL_COMPONENT_H

//Kyle St.Amant
//8/15/2016
//description here

#include "Component.h"

#pragma warning(push)  //Save state
#pragma warning(disable:4127) //disable warning
#pragma warning(disable:4251)
#pragma warning(disable:4100)
#pragma warning(disable:4201) 
#include "GL\glew.h"
#include "gtc/matrix_transform.hpp"			

#pragma warning(pop)

#define V_UP glm::vec3(0,1.0f,0)
#define V_RIGHT glm::vec3(1.0f,0,0)
#define V_FORWARD glm::vec3(0,0,1.0f)


class SpatialComponent : public Component
{
private:

	glm::vec3 m_pos{ glm::vec3() };

	int m_yaw		{ 0 }; // side to side (along up) 
	int m_pitch	{ 0 }; //up/down (along right)
	int m_roll	{ 0 };//Roll along look
						 
	//TODO: remove
	bool  m_constrainPitch{ true };

	glm::vec3 m_lookVec	{glm::vec3(0,0,1.0f) };
	glm::vec3 m_forward {glm::vec3 (0,0,1.0f)};

	glm::vec3 m_right	{glm::vec3(1.0f,0,0) };
	glm::vec3 m_up		{glm::vec3(0,1.0f,0) };

public:

	//static const glm::vec3 UP;// = glm::vec3(0, 1.0f, 0);
	//static const glm::vec3 RIGHT;// = glm::vec3(1.0f, 0, 0);
	//static const glm::vec3 FORWARD;// = glm::vec3(0, 0, -1.0f);

	//degrees
	void SetYaw		(int angle);
	//degrees
	void SetPitch	(int angle);
	//degrees
	void SetRoll	(int angle);

	//degrees
	void AddYaw		(int angle);
	//degrees
	void AddPitch	(int angle);
	//degrees
	void AddRoll	(int angle);

	void SetPos		(glm::vec3 pos);
	void SetPosX(float amount);
	void SetPosY(float amount);
	void SetPosZ(float amount);


	glm::vec3 GetPos();

	//TODO: remove
	void ConstrainPitch(bool constrain = false);

	int GetYaw();
	int GetPitch();
	int GetRoll();
	//glm::mat4 m_translate;
	glm::mat4 m_rotate{ glm::mat4() };
	glm::mat4 m_scale{ glm::mat4() };
	glm::mat4 GetTranslate();
	glm::mat4 GetRotate();
	glm::mat4 GetScale();

	void SetRotate(glm::mat4 mat);
	void SetScale(glm::mat4 mat);
	void SetScale(float scale);
	glm::vec3 GetLookVec();
	glm::vec3 GetRightVec();
	glm::vec3 GetForwardVec();
	glm::vec3 GetUpVec();
	void SetLookVec	  (glm::vec3 vec);
	void SetForwardVec(glm::vec3 vec);
	void SetRightVec  (glm::vec3 vec);
	void SetUpVec	  (glm::vec3 vec);

	bool UpdateRotations(float dt);

	//bool Update(float dt);

};

#endif //def SPACIAL_COMPONENT_H



