#ifndef  PERSPECTIVE_H
#define PERSPECTIVE_H

//Kyle St.Amant
//7/9/2016
//description here


#pragma warning(push)  //Save state																												 
#pragma warning(disable:4201) //disable warnings																								 
																													 
#include "mat4x4.hpp"			

#pragma warning(pop)


class Perspective
{
public:
	void SetPerspective(float fov, float aspect, float zNear, float zFar);
	glm::mat4 GetPerspective();
	//Conveniently returns the new perspective
	void SetAspect(float aspect);

private:

	float m_fov;// = 75.0f;
	float m_aspect;// = static_cast<float>(m_window->width()) / m_window->height();
	float m_zNear;// = 0.01f;
	float m_zFar;// = 100.0f;
	glm::mat4 m_perspective;

};


#endif //def PERSPECTIVE_H

