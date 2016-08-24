#ifndef  ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

//Kyle St.Amant
//8/17/2016
//description here

#include "GraphicalObject.h"
#include "PlayerEntity.h"
#include "AnimatedCubeEntity.h"
#include "CollisionTester.h"
#include "ShapeGenerator.h"
#include <functional>


class EntityManager
{

	enum {
		MAX_ENTITIES = 50
	};
private:
	//GraphicalObject m_playerGob;
	Entity * m_entities[MAX_ENTITIES]{ nullptr };
	PlayerEntity * m_player;
	//CollisionTester m_collisionTester;
	GraphicalObject m_gob;

public:

	//void BuildPlayerEntity(PlayerEntity * player, glm::vec3 pos, glm::vec3 viewDir = glm::vec3(0,0,1.0f));

	bool BuildPlayerEntity(PlayerEntity * player, const char * name, const char * meshFile, const char * texture = "none",std::function <bool(GraphicalObject *, glm::mat4)> drawCallback = nullptr, glm::vec3 pos = glm::vec3());
	bool EntityManager::BuildCubeEntity(AnimatedCubeEntity * player, const char * name, std::function<bool(GraphicalObject*, glm::mat4)> drawCallback = nullptr, glm::vec3 pos = glm::vec3());

	bool AddEntity(Entity * entity, const char * name);
	bool AddCollisionObj(GraphicalObject * gob);

	bool Update(float dt);

};

#endif //def ENTITY_MANAGER_H


