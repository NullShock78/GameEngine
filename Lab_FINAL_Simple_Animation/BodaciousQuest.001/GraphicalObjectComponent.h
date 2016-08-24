#ifndef  GOB_COMPONENT_H
#define GOB_COMPONENT_H

//Kyle St.Amant
//8/15/2016
//description here


#pragma warning(push)  //Save state																												 
#pragma warning(disable:4201) //disable warnings		
#pragma warning(disable:4127)
#pragma warning(disable:4251)
#pragma warning(disable:4100)
//#include "gtc/random.hpp"																														 
#include "gtc/matrix_transform.hpp"			
#pragma warning(pop) 
#include "Component.h"

#include "GraphicalObject.h"
class SpatialComponent;
class GraphicalObjectComponent : public Component
{
public:
	//TODO: move functions from gob to other components
	void SetRotationMat(glm::mat4 mat);

	void SetPos(glm::vec3 pos);
	void SetScale(float scale);
	//void SetRotationMat(glm::mat4 mat);
	void SetTranslateMat(glm::mat4 mat);


	glm::mat4 GetRotationMatrix();
	glm::mat4 GetScaleMatrix();
	glm::mat4 GetTranslateMatrix();

	GraphicalObject * GetGob();

	bool Update(float dt);

	//bool Update(float dt);
	bool Initialize();

	void LookAt(glm::vec3 forward);
private:
	GraphicalObject m_gob;
	SpatialComponent * m_spatial;

};

#endif //def GOB_COMPONENT_H


