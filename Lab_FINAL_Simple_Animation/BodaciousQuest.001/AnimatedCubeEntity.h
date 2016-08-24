#ifndef  ANIMATED_CUBE_ENTITY_H
#define ANIMATED_CUBE_ENTITY_H

//Kyle St.Amant
//8/22/2016
//description here

#include "Entity.h"
#include "BasicAnimationComponent.h"
#include "SpatialComponent.h"
#include "GraphicalObjectComponent.h"
class AnimatedCubeEntity : public Entity
{
private:
	SpatialComponent m_spatial;
	BasicAnimationComponent m_animation;
	GraphicalObjectComponent m_gobComp;
public:

	bool Initialize(glm::vec3 pos = glm::vec3(), glm::vec3 offset = glm::vec3(0,0,0));
	void Start();
	bool Update(float dt);
	GraphicalObject * GetGob();
	glm::vec3 GetPosition();
	void SetPos(glm::vec3 pos);
};


#endif //def ANIMATED_CUBE_ENTITY_H


