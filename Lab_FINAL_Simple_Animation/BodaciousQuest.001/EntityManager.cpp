#include "EntityManager.h"
#include "PlayerEntity.h"
#include "ShapeGenerator.h"
#include "RenderEngine.h"

#include <iostream>

bool EntityManager::BuildPlayerEntity(PlayerEntity * player, const char * name, const char * meshFile, const char * texture, std::function<bool(GraphicalObject*, glm::mat4)> drawCallback, glm::vec3 pos)
{

	ShapeGenerator::MakeCube(&m_gob);
	if(!RenderEngine::AddGraphicalObject(&m_gob))
	{
		return false;
	}


	player->Initialize(pos,glm::vec3(0,3.0f,0));
	m_player = player;
	//std::cout << player;

	if (!ShapeGenerator::ReadSceneFile(meshFile, player->GetGob(), texture))
	{
		GameLogger::Log(LogMsgType::cFatalError, "EntityManager::BuildPlayerEntity(): failed to read scene");
		return false;
	}
	if (!RenderEngine::AddGraphicalObject(player->GetGob()))
	{
		GameLogger::Log(LogMsgType::cFatalError, "EntityManager::BuildPlayerEntity():AddGraphicalObject failed ");
		return false;
	}
	player->GetGob()->m_drawCallback = drawCallback;

	AddEntity(player, name);
	GameLogger::Log(LogMsgType::cInfo, "EntityManager::BuildPlayerEntity(): Built [%s] successfully", name);


	return true;
}

bool EntityManager::BuildCubeEntity(AnimatedCubeEntity * cube, const char * name, std::function<bool(GraphicalObject*, glm::mat4)> drawCallback, glm::vec3 pos)
{
	if (!cube->Initialize()) return false;

	ShapeGenerator::MakeCube(cube->GetGob());
	
	if (!RenderEngine::AddGraphicalObject(cube->GetGob()))
	{
		GameLogger::Log(LogMsgType::cFatalError, "EntityManager::BuildPlayerEntity():AddGraphicalObject failed ");
		return false;
	}

	AddEntity(cube, name);
	return true;
}



bool EntityManager::AddEntity(Entity * entity, const char * name)
{

	if (!entity) {
		GameLogger::Log(LogMsgType::cFatalError, "EntityManager::AddComponent(): Entity[%s]: is nullptr", name);
		return false;
	}
	for (int j = 0; j < MAX_ENTITIES; ++j)
	{
		if (!m_entities[j])
		{
			m_entities[j] = entity;
			entity->SetName(name);
			return true;
		}
	}
	GameLogger::Log(LogMsgType::cFatalError, "EntityManager::AddComponent(): List is full, could not add Entity [%s] ", name);

	return false;
}

bool EntityManager::Update(float dt)
{
	for (int j = 0; j < MAX_ENTITIES; ++j)
	{
		if (m_entities[j])
		{
			bool result = m_entities[j]->Update(dt);
			if (!result)
			{
				GameLogger::Log(LogMsgType::cFatalError, "EntityManager::Update(): Entity[%s] failed to update.", m_entities[j]->GetName());
				return false;
			}
		}
	}

	//Todo: move
	//const float * pos = m_player->GetCamPos();
	//vec3 camPos = m_player->GetCamPosition();//glm::vec3(*pos, *(++pos), *(++pos));
	//glm::vec3 vec = m_player->GetLookVec();
	//float result = m_collisionTester.FindWall(camPos, vec,false);
	//
	//static bool hit = true;
	//glm::vec3 i = m_collisionTester.GetIntersection();
	//m_gob.SetPos(i);

	//if (result < FLT_MAX && hit)
	//{
 //		printf("Distance:[%f] \n", result);
	//	glm::vec3 i = m_collisionTester.GetIntersection();
	//	printf("Intersection: %f %f %f\n", i.x, i.y, i.z);

	//	

	//	hit = false;
	//}
	//else if (result == FLT_MAX)
	//{
	//	hit = true;
	//}


	return true;
}

bool EntityManager::AddCollisionObj(GraphicalObject * gob)
{
	return CollisionTester::AddStaticCollider(gob);
}
