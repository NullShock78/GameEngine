#include "AnimatedCubeEntity.h"

bool AnimatedCubeEntity::Initialize(glm::vec3 pos, glm::vec3 offset)
{

	if (!AddComponent(&m_spatial, "spatial", false)) {
		GameLogger::Log(LogMsgType::cFatalError, "AnimatedCubeEntity::Initialize(): m_spatial failed to add");
		return false;
	}
	if (!AddComponent(&m_gobComp, "gob", false)) {
		GameLogger::Log(LogMsgType::cFatalError, "AnimatedCubeEntity::Initialize(): GobComponent failed to add");
		return false;
	}

	if (!AddComponent(&m_animation, "animation", false)) {
		GameLogger::Log(LogMsgType::cFatalError, "AnimatedCubeEntity::Initialize(): BasicAnimationComponent failed to add");
		return false;
	}


	if (!m_gobComp.Initialize()) {
		GameLogger::Log(LogMsgType::cFatalError, "AnimatedCubeEntity::Initialize(): GobComponent failed to Init");
		return false;
	}
	if (! m_animation.Initialize()) {
		GameLogger::Log(LogMsgType::cFatalError, "AnimatedCubeEntity::Initialize(): BasicAnimationComponent failed to Init");
		return false;
	}
	m_spatial.SetPos(glm::vec3(0,10.0f,0));
	m_spatial.SetScale(1.0f);

	m_animation.QueueAnimation(glm::vec3(0, 1.0f, 0), 4.0f, 0.0f,4.0f);
	m_animation.QueueAnimation(glm::vec3(0, 0, 1.0f), 2.0f, 0.0f, 1.0f);
	m_animation.QueueAnimation(glm::vec3(1.0f, 0,0), 2.0f, 1.0f, 1.0f);
	m_animation.QueueAnimation(glm::vec3(0, 0, -1.0f), 2.0f, 2.0f, 1.0f);
	m_animation.QueueAnimation(glm::vec3(-1.0f, 0, 0), 2.0f, 3.0f, 1.0f);

//	m_animation.QueueAnimation(glm::vec3(1.0f, 0, 0), 10.0f, 0.0f, 1.0f);

	//m_animation.QueueAnimation(glm::vec3(-1.0f, 0, 0), 10.0f, 0.0f, 1.0f);
	//m_animation.QueueAnimation(glm::vec3(0, 0, -1.0f), 10.0f, 1.0f, 2.0f);

	//m_animation.QueueAnimation(glm::vec3(0, -1.0f, 0), 10.0f, 0.0f, 1.0f);

	return true;
}

void AnimatedCubeEntity::Start()
{
	m_animation.Start(0.0f);
}



bool AnimatedCubeEntity::Update(float dt)
{
	for (int j = 0; j < MAX_COMPONENTS; j++)
	{
		if (m_components[j] && m_components[j]->IsEnabled())
		{
			bool result = m_components[j]->Update(dt);
			if (!result) {
				return false;
			}
		}
	}

	return true;
}

GraphicalObject * AnimatedCubeEntity::GetGob()
{
	return m_gobComp.GetGob();
}

glm::vec3 AnimatedCubeEntity::GetPosition()
{
	return m_spatial.GetPos();
}

void AnimatedCubeEntity::SetPos(glm::vec3 pos)
{

	m_spatial.SetPos(glm::vec3(0, 0, 0));
	Start();
}


