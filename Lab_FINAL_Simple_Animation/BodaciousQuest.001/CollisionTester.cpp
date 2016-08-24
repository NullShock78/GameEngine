#include "CollisionTester.h"
#include "GraphicalObject.h"

using glm::vec3;
using glm::cross;

GraphicalObject * CollisionTester::m_head = nullptr;
GraphicalObject * CollisionTester::m_tail = nullptr;

glm::vec3 CollisionTester::GetIntersection()
{
	return m_intersection;
}

float CollisionTester::RayTriangleIntersect(glm::vec3 &p0, glm::vec3 &p1, glm::vec3 &p2, glm::vec3 &positionCastFrom, glm::vec3 &rayDir, glm::vec3 & triNormOut, glm::vec3 & intersection, float minT)
{
	static const float noIntersection = FLT_MAX;

	vec3 e1 = p1 - p0;
	vec3 e2 = p2 - p1;

	vec3 n = cross(e1, e2);
	
	//float dot = glm::dot(n , rayDir);
	float dot = glm::dot(n, rayDir);

	if (!(dot < 0.0f))return noIntersection;
	
	float d = glm::dot(n, p0);
		
	float t = d - glm::dot(n, positionCastFrom);

	if (!(t <= 0.0f)) return noIntersection;

	if(!(t >= dot*minT)) return noIntersection;


	//Do compute


	t /= dot;

	if (!(t >= 0.0f)) {
		return noIntersection;
	}
	if (!(t <= minT)) {
		return noIntersection;
	}


	vec3 p = positionCastFrom + rayDir*t;
	

	//Calculate UVs

	float u0, u1, u2;
	float v0, v1, v2;

	if (fabs(n.x) > fabs(n.y)) {
		if (fabs(n.x) > fabs(n.z)) {
			u0 =  p.y - p0.y;
			u1 = p1.y - p0.y;
			u2 = p2.y - p0.y;

			v0 =  p.z - p0.z;
			v1 = p1.z - p0.z;
			v2 = p2.z - p0.z;
		}
		else
		{
			u0 =  p.x - p0.x;
			u1 = p1.x - p0.x;
			u2 = p2.x - p0.x;

			v0 =  p.y - p0.y;
			v1 = p1.y - p0.y;
			v2 = p2.y - p0.y;
		}

	}
	else {
		if (fabs(n.y) > fabs(n.z))
		{
			u0 =  p.x - p0.x;
			u1 = p1.x - p0.x;
			u2 = p2.x - p0.x;

			v0 =  p.z - p0.z;
			v1 = p1.z - p0.z;
			v2 = p2.z - p0.z;
		}
		else
		{
			u0 =  p.x - p0.x;
			u1 = p1.x - p0.x;
			u2 = p2.x - p0.x;

			v0 =  p.y - p0.y;
			v1 = p1.y - p0.y;
			v2 = p2.y - p0.y;
		}
	}

	//Compute denominator, check for invalid
	//------------------------------------------------------|	!	|
	float temp = u1 * v2 - v1 * u2;
	if (temp == 0.0f)
	{
		return noIntersection;
	}


	temp = 1.0f / temp;

	//Bary--0-=sa0= coords(?) check at each step 
	float alpha = (u0 * v2 - v0 * u2) * temp;
	if (!(alpha >= 0.0f)) {
		return noIntersection;
	}
	float beta = (u1 * v0 - v1 * u0) * temp;
	if (!(beta >= 0.0f)) {
		return noIntersection;
	}

	float gamma = 1.0f - alpha - beta;
	if (!(gamma >= 0.0f)) {
		return noIntersection;
	}
	triNormOut = n;
	intersection = p;
	return t;
}

bool CollisionTester::AddStaticCollider(GraphicalObject * gob)
{
	if (m_head == nullptr)
	{
		m_head = gob;
		m_tail = gob;
		return true;
	}
	else
	{
		m_tail->SetNextCollider(gob);
		m_tail = gob;
	}

	return true;
}

float CollisionTester::FindWall(glm::vec3 fromPos, glm::vec3 rayDir, bool normalized)
{
	float smallest = FLT_MAX;
	GraphicalObject * curGob = m_head;

	vec3 resultNorm;
	vec3 intersectPos;
	vec3 castDir = rayDir;
	if (!normalized)
	{
		castDir = glm::normalize(rayDir);
	}

	while (curGob != NULL)
	{
		RenderInfo * rinfo = curGob->GetRenderInfoPtr();
		float * vertPtr = reinterpret_cast<float*>(curGob->GetMesh()->GetVertexDataStart());

		vec3 p0;
		vec3 p1;
		vec3 p2;


		for (int j = 0; j < rinfo->m_numVerts/3; ++j)
		{

			float * tempVertPtr = vertPtr;

		
			p0.x = *tempVertPtr;
			++tempVertPtr;


			p0.y = *tempVertPtr;
			++tempVertPtr;

			p0.z = *tempVertPtr;

			vertPtr += rinfo->m_stride / sizeof(float);
			tempVertPtr = vertPtr;


			p1.x = *tempVertPtr;
			++tempVertPtr;

			p1.y = *tempVertPtr;
			++tempVertPtr;

			p1.z = *tempVertPtr;
			vertPtr += rinfo->m_stride / sizeof(float);
			tempVertPtr = vertPtr;


			

			p2.x = *tempVertPtr;
			++tempVertPtr;

			p2.y = *tempVertPtr;
			++tempVertPtr;

			p2.z = *tempVertPtr;

			vertPtr += rinfo->m_stride / sizeof(float);


			//glBegin(GL_LINES);
			//glVertex3f(p0.x, p0.y, p0.z);
			//glVertex3f(p2.x, p2.y, p2.z);
			//glVertex3f(p1.x, p1.y, p1.z);
			//glEnd();

			glm::mat4 objMat = (curGob->GetTranslateMatrix() * (curGob->GetRotationMatrix() * curGob->GetScaleMatrix()));

			p0 = vec3(objMat * glm::vec4(p0, 1.0f)); //(curGob->GetPos() + vec3(curGob->GetRotationMatrix() * glm::vec4(p0, 1.0f)));
			p1 = vec3(objMat * glm::vec4(p1, 1.0f));
			p2 = vec3(objMat * glm::vec4(p2, 1.0f));

			

			float dist = RayTriangleIntersect(p0, p1, p2, fromPos, castDir, resultNorm, intersectPos, smallest);

			if (dist < smallest)
			{
				smallest = dist;
				m_intersection = intersectPos;
				//m_intersectMat = objMat;
			}
			
			
		}
		curGob = curGob->GetNextCollider();
	}
	//m_intersection = glm::vec3(m_intersectMat * glm::vec4(m_intersection, 0.0f));
	return smallest;
}
