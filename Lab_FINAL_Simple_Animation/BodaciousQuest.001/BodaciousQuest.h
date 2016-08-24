#ifndef  BODACIOUS_QUEST_H
#define BODACIOUS_QUEST_H
#include "ShaderProgram.h"

//Kyle St.Amant
//6/21/2016
//Game class
#pragma warning(push)  //Save state
#pragma warning(disable:4127) //disable warning
#pragma warning(disable:4251)
#pragma warning(disable:4100)
#include "GL\glew.h"

#pragma warning(pop) //return to previous warning state
#include "CubeManager.h"
#include "Perspective.h"
#include "Camera.h"
#include "Keyboard.h"
#include "TextureManager.h"
#include "PlayerEntity.h"
#include "EntityManager.h"
#include "AnimatedCubeEntity.h"

//Predeclare



class MyWindow;
class QMouseEvent;
class ConfigReader;
class BodaciousQuest
{
public:
	bool Initialize(MyWindow * window, ConfigReader * config);
	bool Shutdown();

	static bool LightingCallback(GraphicalObject * gob, glm::mat4 screenMat);

	static bool TextureLightingCallback(GraphicalObject * gob, glm::mat4 screenMat);

	static bool WaterCallback(GraphicalObject * gob, glm::mat4 screenMat);

	

	void Update(float dt);
	//void CombineMatrices();
	void Draw(); 
	static void UpdateDargonCol();
	void MouseMove(QMouseEvent * e);
	void OnResizeWindow();

private:

	
	bool GetConfigValues();
	bool KeyIsDown(int vKey);
	void ProcessInput(float dt);
	bool InitializeGL();
	
	void GetPerspective();
	
	void ShowFrameRate(float dt);
private:

	bool m_carryCube{ false };
	bool m_carryDargon{ false };
	bool m_dargonLookat{ false };
	bool m_carryChicken{ false };
	static float m_time;// { 0.0f };
	static bool m_timeForward;
	const float FB_DRAW_TIME = 1.0f;
	bool fb_switch{ true };
	bool m_lockOn{ false };
	//void CheckPauseStatus();
	MyWindow   *  m_window{ nullptr };
	static ConfigReader * m_config;
	ShaderProgram m_program;
	CubeManager m_cubeManager;
	Perspective m_perspective;
	Perspective m_perspective2;
	static Camera		m_camera;
	Camera		m_mirrorCam;
	bool m_paused;
	bool m_walk;
	GraphicalObject pyramid;
	GraphicalObject cube;
	GraphicalObject pyramid2;
	GraphicalObject cube2;

	GraphicalObject m_grid;
	GraphicalObject m_debugCube;
	GraphicalObject m_debugSphere;
	GraphicalObject m_readObj;
	GraphicalObject m_readObj2;
	GraphicalObject m_rotatingSphere;
	GraphicalObject m_hideout;
	GraphicalObject m_litPlane;
	GraphicalObject m_litCube;
	GraphicalObject m_litPyramid;
	GraphicalObject m_skybox;

	PlayerEntity m_player;
	AnimatedCubeEntity m_cubeAnimated;

	GraphicalObject * m_playerGob;
	static const float * m_playerCam;

	static GraphicalObject m_dargon;
	GraphicalObject m_texdargon;
	GraphicalObject m_texPlane;
	GraphicalObject m_waterPlane;



	static GraphicalObject m_specialCube;
	GraphicalObject m_chicken;


	EntityManager m_entityManager;


	//GraphicalObject m_chicken;
	int m_width, m_height;

	bool m_showFullScreen;
	bool m_enableControls;
	Keyboard m_keyboard;
	float m_fpsInterval = 0;
	const float m_fov{ 60.0f };
	const float m_zNear{ 0.01f };
	const float m_zFar{ 1000.0f };
	bool ReloadConfig();

	static float m_ambientReflectivity;// { 0.5f };
	static float m_diffuseReflectivity;// { 0.5f };
	static float m_specularReflectivity;// { 0.5f };
	static float m_specularShininess;// { 0.5f };
	static float m_falloffA;
	static float m_falloffB;
	static float m_falloffC;
	static bool	 m_directionalLight;

	static glm::vec3 m_ambientCol;// { glm::vec3(0, 0, 0) };
	static glm::vec3 m_diffuseCol;// { glm::vec3(0, 0, 0) };
	static glm::vec3 m_specularCol;// { glm::vec3(0, 0, 0) };
	
	

	static void UpdateCubePos();
	static void UpdateLightVals();
};


#endif //def BODACIOUS_QUEST_H


