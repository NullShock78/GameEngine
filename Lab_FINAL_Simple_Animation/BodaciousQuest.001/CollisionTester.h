#ifndef  COLLISION_TESTER_H
#define COLLISION_TESTER_H

//Kyle St.Amant
//8/18/2016
//Triangle collision class

#pragma warning(push)  //Save state
#pragma warning(disable:4127) //disable warning
#pragma warning(disable:4251)
#pragma warning(disable:4100)
#pragma warning(disable:4201)

#include "vec3.hpp"
#include "gtc/matrix_transform.hpp"	
#pragma warning(pop)

class GraphicalObject;
class CollisionTester
{
	struct ColliderNode
	{
		GraphicalObject * gob{ nullptr };
		int stride;

	};


private:
	static GraphicalObject * m_head; //{ nullptr };
	static GraphicalObject * m_tail;// { nullptr };
	int m_numTris;
	glm::vec3 m_intersection{ glm::vec3() };
	glm::mat4 m_intersectMat{ glm::mat4() };
public:
	glm::vec3 GetIntersection();
	float RayTriangleIntersect(glm::vec3 & p0, glm::vec3 & p1, glm::vec3 & p2, glm::vec3 & positionCastFrom, glm::vec3 & rayDir, glm::vec3 & triNormOut, glm::vec3 & intersection, float minT = 1.0f);
	static bool AddStaticCollider(GraphicalObject * gob);
	//float CheckAgainstList(GraphicalObject * collider1);
	float FindWall(glm::vec3 fromPos, glm::vec3 rayDir, bool normalized = true);
};
#endif //def COLLISION_TESTER_H
