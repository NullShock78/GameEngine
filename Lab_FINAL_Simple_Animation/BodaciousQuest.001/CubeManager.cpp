#include "CubeManager.h"
const GLsizei BUFFER_SIZE = 1000000;
#include "MyGL.h"
#include "GameLogger.h"
#include "ShapeGenerator.h"
#include "ShaderProgram.h"

#pragma warning(push)  //Save state																												 
#pragma warning(disable:4201) //disable warnings																								 																									 
#include "gtc/matrix_transform.hpp"		
#include "gtc/random.hpp"	
#pragma warning(pop) //return to previous warning state			
#include "RenderEngine.h"

bool CubeManager::Initialize(ShaderProgram * shaderProgram)
{

	m_shaderProgramPtr = shaderProgram;

	//Sets uniforms
	GetUniforms();
	/*ShapeGenerator::MakePyramid(&pyramid2);
	ShapeGenerator::MakePyramid(&pyramid);

	RenderEngine::AddGraphicalObject(&pyramid);
	RenderEngine::AddGraphicalObject(&pyramid2);*/

	InitializeCubes();


	GameLogger::Log(LogMsgType::cProcess, "CubeManager::Initialize() successful.");
	return true;
}

bool CubeManager::Shutdown()
{
	GameLogger::Log(LogMsgType::cProcess, "CubeManager::Shutdown() successful.");
	return true;
}

//------------------------------------------------||	UPDATE    ||--------------------------------------
void CubeManager::Update(float dt)
{
	
	float angle = 0.01f;

	for (int j = 0; j < NUM_CUBES; ++j)
	{
		float newAngle = (30.0f + (angle * j))  * dt;
		m_cubes[j].Rotate(newAngle);
	}


	/*m_cubes[0].Rotate(angle);
	m_cubes[1].Rotate(angle);
	m_cubes[2].Rotate(angle);
	m_cubes[3].Rotate(angle);
	m_cubes[4].Rotate(-angle);*/
	

}


//------------------------------------------------------------------------------------------------------------------


//TODO: remove
void CubeManager::AlignCube(int index, float degrees)
{
	if (index >= 0 && index < NUM_CUBES) {
		m_cubes[index].SetAlignedToAxisAndRotation(degrees);
	}
}

void CubeManager::RotateCube(int index, float degrees, glm::vec3 axis)
{

	if (index >= 0 && index < NUM_CUBES) {
		glm::vec3 the_axis;

		if (axis.x == 999.0f)
		{
			m_cubes[index].Rotate(degrees);
			return;
		}
		else
		{
			the_axis = m_cubes[index].GetRotateAxis();
			m_cubes[index].SetRotationAxis(axis);
			m_cubes[index].Rotate(degrees);
			m_cubes[index].SetRotationAxis(the_axis);

		}	
	}
}
//Commented out for issues.
void CubeManager::RotateCubeRotAxis(int /*index*/, int /*dx*/, int /*dy*/)
{

}

//Initializes uniform location ids
bool CubeManager::GetUniforms()
{
	m_uniformLocCol = m_shaderProgramPtr->GetUniformLocation("colorin");
	m_uniformLocMat4 = m_shaderProgramPtr->GetUniformLocation("MAT");
	if (m_uniformLocCol < 0)
	{
		GameLogger::Log(LogMsgType::cFatalError, "CubeManager::GetUniforms(): m_uniformLocCol < 0.");
		return false;
	}
	if (m_uniformLocMat4 < 0)
	{
		GameLogger::Log(LogMsgType::cFatalError, "CubeManager::GetUniforms(): m_uniformLocMat4 < 0.");
		return false;
	}

	return true;
}


//Initializes data
bool CubeManager::FillBuffers()
{
	//bufContentSizeVertex = bufContentSizeIndex = 0;

	
	return true;
}

//Set Mat4s
void CubeManager::InitializeCubes()
{
	for (int j = 0; j < NUM_CUBES; ++j)
	{
		ShapeGenerator::ReadSceneFile( "..\\Data\\Scenes\\Chicken.pc.scene",&m_cubes[j]);
	}
	for (int j = 0; j < NUM_CUBES; ++j)
	{
		RenderEngine::AddGraphicalObject(&m_cubes[j]);
	}
	//int numCubes  NUM_CUBES;
	//printf("hi");

	int cur_cube = 0;

	for (int j = 0; j < 10; ++j)
	{
		for (int k = 0; k < 10; ++k)
		{
			for (int l = 0; l < 10; ++l)
			{
				InitCube(cur_cube, glm::vec3(((float)j)+ 2.0f, ((float)k) + 2.0f, -(float)l), glm::vec3(.5f, .5f, .5f), glm::vec3(glm::linearRand(0.01f, 0.6f), glm::linearRand(0.01f, 0.6f), glm::linearRand(0.01f, 0.6f)), glm::vec3(0.0f, 1.0f, 0.0f));//all
				m_cubes[cur_cube].Rotate(45.0f);
				m_cubes[cur_cube].SetRotationAxis(glm::vec3(1.0f,1.0f, 0.25f));
				++cur_cube;
			}
		}
	}


	InitCube(0, glm::vec3(0, 0,				 -1.0f), glm::vec3(.25f, .25f, .25f), glm::vec3(glm::linearRand(0.21f, 0.75f), 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//all
	m_cubes[0].Rotate(45.0f);
	m_cubes[0].SetRotationAxis(glm::vec3(1.0f,1.0f, 0.25f));
	InitCube(1, glm::vec3(-6.0f, 5.0f,		-12.0f), glm::vec3(.75f, .75f, .75f), glm::vec3(0.0f, glm::linearRand(0.21f, 0.75f), 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));//x
	InitCube(2, glm::vec3( 1.0f, 0.9f,		 -2.0f), glm::vec3(.15f, .15f, .15f), glm::vec3(glm::linearRand(0.21f, 0.75f), 0.0f, glm::linearRand(0.21f, 0.75f)), glm::vec3(0.0f, 1.0f, 0.0f));//y
	InitCube(3, glm::vec3(1.5f, -1.2f,	     -3.0f), glm::vec3(.2f, .2f, .2f), glm::vec3(0.0f, 0.0f, glm::linearRand(0.21f, 0.75f)), glm::vec3(0.0f, 0.0f, 1.0f));//z
	InitCube(4, glm::vec3(-165.0f,-130.0f, -350.0f), glm::vec3(30.0f,30.0f, 30.0f), glm::vec3(glm::linearRand(0.21f, 0.75f), 0.0f, glm::linearRand(0.21f, 0.75f)), glm::vec3(0.0f, 1.0f, 0.0f));//first opposite
	m_cubes[4].Rotate(45.0f);
	m_cubes[4].SetRotationAxis(glm::vec3(1.0f, 0.5f, 0.25f));

	GameLogger::Log(LogMsgType::cDebug, "CubeManager::InitializeCubes() successful.");
}

void CubeManager::InitCube(int index, glm::vec3 pos, glm::vec3 scale, glm::vec3 col, glm::vec3 rotationAxis)
{
	m_cubes[index].SetScaleMatrix(glm::scale(glm::mat4(), scale));
	m_cubes[index].SetTranslateMatrix(glm::translate(glm::mat4(), pos));
	m_cubes[index].SetRotationMatrix(glm::mat4());
	m_cubes[index].SetRotateAngle(0.0f);
	m_cubes[index].SetRotationAxis(rotationAxis);
	m_cubes[index].SetTint(col);
}
