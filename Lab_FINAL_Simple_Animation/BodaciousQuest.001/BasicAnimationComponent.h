#ifndef  BASIC_ANIMATION_COMPONENT
#define BASIC_ANIMATION_COMPONENT

//Kyle St.Amant
//8/16/2016
//To work on in free time.
#pragma warning(push)  //Save state
#pragma warning(disable:4127) //disable warning
#pragma warning(disable:4251)
#pragma warning(disable:4100)
#pragma warning(disable:4201)
#include "vec3.hpp"
#include "gtc/matrix_transform.hpp"	
#pragma warning(pop)

#include "Component.h"



class SpatialComponent;
class BasicAnimationComponent : public Component
{
	
public:	
	struct BasicAnimation
	{
		bool m_enabled;
		bool m_finished;
		bool m_started;

		glm::vec3 dir;
		float m_startTime;
		float m_time;
		float m_endTime;
	};
private:

	const int NUM_ANIMATIONS = 50;
	bool m_animating{ false };
	float time{ 0.0f };
	BasicAnimation m_animations[50];
	int m_currentAnimation;

	SpatialComponent * m_spatial;
public:

	


	bool Initialize();
	bool Update(float dt);
	
	void QueueAnimation(glm::vec3 startPos, glm::vec3 endPos, float startTime, float endTime);
	void QueueAnimation(glm::vec3 dir, float speed, float startTime, float endTime);

	void QueueLocalAnimation(glm::vec3 dir, float speed, float startTime, float duration);

	void ClearAnimations();
	void Start(float startTime = 0.0f);
	void Stop();
};
#endif //def BASIC_ANIMATION_COMPONENT


