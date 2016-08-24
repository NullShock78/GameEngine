#include "BasicAnimationComponent.h"
#include "SpatialComponent.h"
bool BasicAnimationComponent::Initialize()
{
	m_spatial = GetSiblingComponent<SpatialComponent>();
	if (!m_spatial) return false;
	m_currentAnimation = 0;
	m_animating = false;
	return true;
}

bool BasicAnimationComponent::Update(float dt)
{

	if (m_animating) {
		time += dt;

		for (int j = 0; j < NUM_ANIMATIONS; j++)
		{

			
			if (m_animations[j].m_enabled)
			{

				if (!m_animations[j].m_started)
				{
					if (m_animations[j].m_startTime <= time)
					{
						m_animations[j].m_started = true;
					}
				}
				else if (!m_animations[j].m_finished)
				{
					m_animations[j].m_time += dt;
					if (m_animations[j].m_time >= m_animations[j].m_endTime) m_animations[j].m_finished = true;

					if (!m_animations[j].m_finished) {
						m_spatial->SetPos(m_spatial->GetPos() + (m_animations[j].dir * dt));
					}
				}
			}
		}
	}

	return true;
}

void BasicAnimationComponent::QueueAnimation(glm::vec3 startPos, glm::vec3 endPos, float startTime, float endTime)
{
	m_animations[m_currentAnimation]={
		true,
		false,
		false,
		glm::vec3(endPos - startPos),
		startTime,
		0.0f,
		endTime
	};
	++m_currentAnimation;
}

void BasicAnimationComponent::QueueAnimation(glm::vec3 dir, float speed, float startTime, float endTime)
{
	glm::vec3 t_dir = glm::normalize(dir);
	m_animations[m_currentAnimation] = {
		true,
		false,
		false,
		(t_dir * speed),
		startTime,
		0.0f,
		endTime
	};
	++m_currentAnimation;
}

void BasicAnimationComponent::QueueLocalAnimation(glm::vec3 dir, float speed, float startTime, float duration)
{

	glm::vec3 z = m_spatial->GetLookVec();
	glm::vec3 x = m_spatial->GetRightVec();
	glm::vec3 y = m_spatial->GetUpVec();
	//glm::mat4 newMat = glm::mat4(x.x, x.y, x.z, 0.0f, y.x, y.y, y.z, 0.0f, z.x, z.y, z.z, 0.0f, 0, 0, 0, 1);
//	m_spatial->SetRightVec(x);

	glm::vec3 t_dir = glm::normalize((dir.x * x) + (dir.y * y) + (dir.z * z));
	m_animations[m_currentAnimation] = {
		true,
		false,
		false,
		(t_dir * speed),
		startTime,
		0.0f,
		duration
	};
	++m_currentAnimation;
}


void BasicAnimationComponent::ClearAnimations()
{
	for (int j = 0; j < NUM_ANIMATIONS; j++)
	{
		m_animations[j].m_finished = false;
		m_animations[j].m_time = 0.0f;
		m_animations[j].m_started = false;
	}

}

void BasicAnimationComponent::Start(float startTime)
{
	ClearAnimations();

	time = startTime;
	m_animating = true;
}

void BasicAnimationComponent::Stop()
{
	m_animating = true;
}
