#include "BodaciousQuest.h"																														 
#include "MyWindow.h"																															 
#include <iostream>																																 
#include "GameLogger.h"																															 
#include "MyGL.h"																																 
#include "ShapeGenerator.h"																														 
#include "ConfigReader.h"
#include "ShaderManager.h"

#pragma warning(push)  //Save state																												 
#pragma warning(disable:4201) //disable warnings		
#pragma warning(disable:4127)
#pragma warning(disable:4251)
//#include "gtc/random.hpp"																														 
#include "gtc/matrix_transform.hpp"			
#include <QtGui\qmouseevent>
#pragma warning(pop) //return to previous warning state																							 

//#include "BufferManager.h"
#include "RenderEngine.h"

Camera BodaciousQuest::m_camera;
GraphicalObject BodaciousQuest::m_specialCube;
ConfigReader * BodaciousQuest::m_config;
using glm::mat4;
glm::mat4 m_perspectiveMat = glm::mat4();

glm::mat4 m_perspectiveMat2 = glm::mat4();

bool m_running = false;

//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//TODO:
//	1.) Finish Lab 10
//	2.) Create Shader Uniform access seperate from render engine somehow...
//	
//
//
//
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------

bool BodaciousQuest::Initialize(MyWindow * window, ConfigReader * config)
{
	

	m_window = window;
	m_config = config;
	m_config->RegisterForOnUpdate(UpdateCubePos);
	glClearColor(0.5f, 0.5f, 0.0f, 1.0f);
	m_fpsInterval = 1.0f;
	if (!TextureManager::Initialize()) {
		Shutdown(); return false; 
	}
	if (!InitializeGL())
	{
		GameLogger::Log(LogMsgType::cFatalError, "BodaciousQuest::Initialize(): InitializeGL() failed");
		Shutdown(); 
		return false;
	}
	
	

	//Seperated  for future use
	if (!RenderEngine::Initialize(&m_program)) { Shutdown(); return false; }
	
	
	if (!ShapeGenerator::Initialize(m_config)) { Shutdown(); return false; }
	if (!GetConfigValues()) return false;

	if (m_showFullScreen) {
		window->showFullScreen();
	}

	//m_qstring = QString("HELLO");
	//InitMat4s();




	

	


	//if (!RenderEngine::Initialize()) return false;

	if (!m_camera.Initialize(.015f)) { Shutdown(); return false; }
	


	//Initializes perspective class
	GetPerspective();




	m_keyboard.Initialize(config);
	
	//m_keyboard.AddKey('P');
	m_keyboard.AddKey('1');
	m_keyboard.AddKey('2');
	m_keyboard.AddKey('0');
	m_keyboard.AddKey('9');
	m_keyboard.AddKey('X');
	m_keyboard.AddKey('Q');
	m_keyboard.AddKey('E');
	m_keyboard.AddKey('T');
	m_keyboard.AddKey('O');
	m_keyboard.AddKey('R');
	m_keyboard.AddKey('F');
	m_keyboard.AddKey('V');
	m_keyboard.AddKey('Y');
	m_keyboard.AddKey('H');
	m_keyboard.AddKey('C');
	m_keyboard.AddKey(VK_SHIFT);
	m_keyboard.AddKey(VK_SPACE);
	m_paused = false;
	m_keyboard.AddToggle('P', &m_paused,false);
	m_keyboard.AddToggle('3', &m_walk, true);
	m_keyboard.AddToggle('4', &fb_switch, true);
	if(!m_keyboard.AddToggle('5', &m_lockOn, true)) return false;
	if (!m_keyboard.AddToggle('6', &m_carryChicken, false)) return false;
	if (!m_keyboard.AddToggle('7', &m_carryDargon, false)) return false;
	if (!m_keyboard.AddToggle('8', &m_dargonLookat, false)) return false;

	m_carryChicken = false;
	m_carryDargon  = false;
	m_dargonLookat = false;
	//if(!m_keyboard.AddToggle('9', &m_carryCube, true))return false;;
	/*cube.SetTranslateMatrix(glm::translate(glm::mat4(), glm::vec3(0, 1.0f, -5.0f)));
	cube.SetScaleMatrix(glm::scale(glm::mat4(), glm::vec3(.25f, .25f, .25f)));
	cube2.SetTranslateMatrix(glm::translate(glm::mat4(), glm::vec3(0, -1.0f, -5.0f)));
	cube2.SetScaleMatrix(glm::scale(glm::mat4(), glm::vec3(.25f, .25f, .25f)));*/

	//pyramid.SetTranslateMatrix(glm::translate(glm::mat4(), glm::vec3(2.0f, 2.0f, -5.0f)));
	//pyramid.SetScaleMatrix(glm::scale(glm::mat4(), glm::vec3(.7f, .7f, .7f)));
	//pyramid2.SetTranslateMatrix(glm::translate(glm::mat4(), glm::vec3(-2.0f, -2.0f, -5.0f)));
	//pyramid2.SetScaleMatrix(glm::scale(glm::mat4(), glm::vec3(.7f, .7f, .7f)));



	//ShapeGenerator::MakeTexturedPlane(&m_texPlane);
	//if (!RenderEngine::AddGraphicalObject(&m_texPlane)) { Shutdown(); return false; }
	//m_texPlane.SetPos(glm::vec3(0.0f, -5.0f, -10.0f));
	//m_texPlane.SetScaleMatrix(glm::scale(glm::mat4(), glm::vec3(20.0f, 20.0f, 1.0f)));
	


	//m_mirrorCam
	//ShapeGenerator::MakeSphere(&m_debugSphere,glm::vec3(1.0f,1.0f,0.0f) );
	//m_debugSphere.SetScaleMatrix(glm::scale(glm::mat4(), glm::vec3(10.0f, 10.0f, 10.0f)));
	


	

	//if (!m_cubeManager.Initialize(&m_program)) return false;
	

	//ShapeGenerator::MakePyramid(&pyramid2);
	//ShapeGenerator::MakePyramid(&pyramid);

	//if (!RenderEngine::AddGraphicalObject(&pyramid))return false;
	//if (!RenderEngine::AddGraphicalObject(&pyramid2))return false;

	//ShapeGenerator::MakeGrid(&m_grid, glm::vec3(1.0f, 0.0f, 1.0f));
	//m_grid.SetRotationAxis(glm::vec3(1.0f, 1.0f, 0.25f));
	//if (!RenderEngine::AddGraphicalObject(&m_grid)) return false;
	//ShapeGenerator::MakeSpecialCube(&m_specialCube);
	//if (!RenderEngine::AddGraphicalObject(&m_specialCube)) { Shutdown(); return false; }



	//if (!ShapeGenerator::ReadSceneFile("..\\Data\\Scenes\\Cube.pn.scene", &m_specialCube/*, "..\\Data\\Textures\\world_texture.bmp"*/))
	//{
	//	Shutdown();
	//	return false;
	//}
	ShapeGenerator::MakeSpecialCube(&m_specialCube);
	if (!RenderEngine::AddGraphicalObject(&m_specialCube))
	{
		Shutdown();
		return false;
	}
	m_specialCube.SetTint(0.0f, 1.0f, 1.0f);
	m_specialCube.SetScale(.3f);
	glm::vec3 lightPos = glm::vec3();
	if (!config->GetFloatsForKey("BodaciousQuest.LightingTest.Light.Position", 3, &lightPos[0])) return false;
	m_specialCube.SetPos(lightPos);





	//ShapeGenerator::MakeDebugCube(&m_debugCube, glm::vec3(.50f, .50f, 0.0f));
	//if (!RenderEngine::AddGraphicalObject(&m_debugCube)) { Shutdown(); return false; }
	

	//ShapeGenerator::MakeDebugCube(&m_readObj, glm::vec3(1.0f, 1.0f, 0.0f));
	//if (!RenderEngine::AddGraphicalObject(&m_readObj)) { Shutdown(); return false; }

	//==========================================================================
	//==========================================================================
	//==========================================================================
	//==========================================================================
	//==========================================================================
	ShapeGenerator::MakeCube(&cube);
	if (!RenderEngine::AddGraphicalObject(&cube)) { Shutdown(); return false; }
	cube.SetPos(glm::vec3(0, 1.0f, -5.0f));
	cube.SetRotationAxis(glm::vec3(1.0f, 1.0f, 0.0f));
	//==========================================================================
	//==========================================================================
	//==========================================================================
	//==========================================================================
	//==========================================================================

	/*ShapeGenerator::MakeSphere(&m_readObj2, glm::vec3(1.0f, 0.0f, 1.0f));
	m_readObj2.SetPos(glm::vec3(3.0f, 3.0f, -1.0f));
	if (!RenderEngine::AddGraphicalObject(&m_readObj2)) { Shutdown(); return false; }*/

	ShapeGenerator::MakeSphere(&m_readObj3, glm::vec3(0.0f,1.0f,1.0f));
	if (!RenderEngine::AddGraphicalObject(&m_readObj3)) { Shutdown(); return false; }
	m_readObj3.SetPos(glm::vec3(-1.0f, 5.0f, 1.0f));
	m_readObj3.SetRotationAxis(glm::vec3(1.0f, 0, 0));
	
	/*if (!ShapeGenerator::ReadSceneFile("..\\Data\\Scenes\\Chicken.pc.scene", &m_readObj4))
	{
		GameLogger::Log(LogMsgType::cFatalError, "Failed to read scene file");

		return false;


	}
	if (!RenderEngine::AddGraphicalObject(&m_readObj4)) return false;*/
	
	cube.SetPos(glm::vec3(-3.0f, 7.0f, 0));

	m_readObj.SetPos(glm::vec3(0, 0, -1.0f));

	ShapeGenerator::MakeGrid(&m_grid, glm::vec3(1, 0, 0));
	if (!RenderEngine::AddGraphicalObject(&m_grid))
	{
		Shutdown();
		return false;
	}

	//m_grid.SetPos(glm::vec3(0, -10.0f, 0));
	m_grid.SetPos(glm::vec3(0, -40.0f, 0));
	if (!ShapeGenerator::ReadSceneFile("..\\Data\\Scenes\\AIWorld.pt.scene", &m_chicken, "..\\Data\\Textures\\world_texture.bmp"))
	{ 
		Shutdown(); 
		return false; 
	}
	
	if(!RenderEngine::AddGraphicalObject(&m_chicken))
	{
		Shutdown();
		return false;
	}
	m_chicken.SetTint(1.0f, 1.0f, 1.0f);
	m_chicken.SetScale(.2f);
	m_chicken.SetPos(glm::vec3(0, -20.0f, 0));
	m_chicken.SetRotationAxis(glm::vec3( 0.0f, 0.0f, 1.0f));
	m_chicken.Rotate(90.0f);
	//m_chicken.m_drawCallback = TextureLightingCallback;



	if (!ShapeGenerator::ReadSceneFile("..\\Data\\Scenes\\WaterPlane.ptn.scene", &m_waterPlane))
	{
		Shutdown();
		return false;
	}

	if (!RenderEngine::AddGraphicalObject(&m_waterPlane))
	{
		Shutdown();
		return false;
	}
	m_waterPlane.SetTint(.8f, .85f, .7f);
	m_waterPlane.SetPos(glm::vec3(0, -10.0f, 0));
	m_waterPlane.SetRotationAxis(glm::vec3(1.0f, 0.0f, 0.0f));
	m_waterPlane.Rotate(-90.0f);
	m_waterPlane.SetTexture(TextureManager::GetFrameBufferTexID());
	m_waterPlane.SetNormalTexture(TextureManager::LoadGameBitmap("..\\Data\\Textures\\WaterNormal.bmp"));
	m_waterPlane.m_drawCallback = WaterCallback;
	if (!m_mirrorCam.Initialize(0.015f, m_waterPlane.GetPos() + glm::vec3(0.0f,0.3f,0.0f), glm::vec3(0, 1.0f, 0.0f))) { Shutdown(); return false; }


	//RenderEngine::AttachLight(&m_chicken, &m_specialCube);
	//m_chicken.m_drawCallback = LightingCallback;

	//if (!ShapeGenerator::ReadSceneFile("..\\Data\\Scenes\\Chicken.pt.scene", &m_chicken, "..\\Data\\Textures\\ChickenUVTexture.bmp"))
	//{
	//	Shutdown();
	//	return false;
	//}

	//if (!RenderEngine::AddGraphicalObject(&m_chicken))
	//{
	//	Shutdown();
	//	return false;
	//}


	//m_chicken.SetPos(glm::vec3(0, -3.0f, 0));


	if (!ShapeGenerator::ReadSceneFile("..\\Data\\Scenes\\Dargon.ptn.scene", &m_dargon, "..\\Data\\Textures\\DargonSkin.bmp"))
	{
		Shutdown();
		return false;
	}

	if (!RenderEngine::AddGraphicalObject(&m_dargon))
	{
		Shutdown();
		return false;
	}

	m_dargon.SetRotationAxis(glm::vec3(0, 1.0f, 0));
	//m_dargon.SetTint(0.0f, 1.0f, 0.0f);
	m_dargon.SetPos(glm::vec3(0, -3.0f, 0));
	m_dargon.m_drawCallback = TextureLightingCallback;
	/*if (!ShapeGenerator::ReadSceneFile("..\\Data\\Scenes\\AIWorld.ptn.scene", &m_hideout, "..\\Data\\Textures\\world_texture.bmp"))
	{
		Shutdown();
		return false;
	}

	if (!RenderEngine::AddGraphicalObject(&m_hideout))
	{
		Shutdown();
		return false;
	}
	m_hideout.SetPos(glm::vec3(0.0f, -2.0f, 0.0f));*/
	//m_mirrorCam.SetPos(m_texPlane.GetPos());
	//m_mirrorCam.RotateVec(180.0f, 0.0f);


//	m_readObj3.SetPos(glm::vec3(0, -20.0f, 0));
	//m_readObj4.SetPos(glm::vec3(-10.0f, -2.0f, 0));
	//m_readObj3.SetScaleMatrix(glm::scale(glm::mat4(), glm::vec3(.2f, .2f, .2f)));


	m_window->setFocusPolicy(Qt::StrongFocus);
	m_running = true;
	GameLogger::Log(LogMsgType::cProcess, "BodaciousQuest::Initialize() successful.");
	MyGL::TestForError(LogMsgType::cError, "Errors accrued during game init");
	return true;
}

bool BodaciousQuest::Shutdown()
{
	m_running = false;
	bool retval = true;

	if (!TextureManager::Shutdown()) { retval = false; };
	if (!RenderEngine::Shutdown()) {  retval = false; };
	
	if (!m_camera.Shutdown()) {  retval = false; };
	//if (!m_cubeManager.Shutdown()) { m_window->Shutdown(); retval = false; };
	//if (!m_program.Shutdown()) { m_window->Shutdown(); retval = false; };
	if (!ShaderManager::Shutdown()) {  retval = false; };
	if (!m_window->Shutdown())     retval = false;

	if (retval) {
		GameLogger::Log(LogMsgType::cProcess, "BodaciousQuest::Shutdown() successful.");
	}
	
	return retval;
}

//TODO: manager
bool BodaciousQuest::LightingCallback(GraphicalObject * gob, glm::mat4 screenMat)
{
	MyGL::TestForError(LogMsgType::cFatalError, "BEFORE failed, ok");

	glUniform3fv(15, 1, (GLfloat*)gob->GetTint());
	if (MyGL::TestForError(LogMsgType::cFatalError, " uniLight failed")) return false;

	//glUniform1i()
	glUniformMatrix4fv(20, 1, GL_FALSE, &(gob->GetRotationMatrix() * gob->GetScaleMatrix())[0][0]);

	glUniform3fv(22, 1, &m_specialCube.GetPos()[0]);

	if (MyGL::TestForError(LogMsgType::cFatalError, "glUniform3fv(): 22, Temp light failed"))return false;
	glUniform3fv(23, 1, &m_specialCube.GetPos()[0]);
	//if (MyGL::TestForError(LogMsgType::cFatalError, "glUniform3fv(): 23, Temp light dir failed"))return false;
	//glUniform3fv(19, 1, (GLfloat*)&(gob->GetPos().x));

	float * pos = gob->GetPosX();
	glUniform3fv(19, 1, pos);
	glUniformMatrix4fv(16, 1, GL_FALSE, &screenMat[0][0]);
	return true;
}

bool BodaciousQuest::TextureLightingCallback(GraphicalObject * gob, glm::mat4 screenMat)
{
	//static const GLfloat tempLight[3] = { 0.0f, 1.0f, 0.0f };

	

	//glActiveTexture(GL_TEXTURE0);
	glUniform1i(20, 0);
	glActiveTexture(GL_TEXTURE0);
	TextureManager::BindImageByID(gob->GetTexture());
	if (MyGL::TestForError(LogMsgType::cFatalError, "TextureLightingCallback(): BindImageByID failed"))return false;

	//glUniform1i(20 , gob->GetTexture());
	glUniformMatrix4fv(21, 1, GL_FALSE, &(gob->GetRotationMatrix() * gob->GetScaleMatrix())[0][0]);
	if (MyGL::TestForError(LogMsgType::cFatalError, "Scale Mat failed"))
	{
		return false;
	}
	//23
	//	24
	glUniform3fv(23, 1, gob->GetPosX());
	if (MyGL::TestForError(LogMsgType::cFatalError, "gob pos failed")) return false;

	glUniform3fv(24, 1, &m_camera.GetPosition()[0]);
	if (MyGL::TestForError(LogMsgType::cFatalError, "m_camera pos failed")) return false;

	glUniform3fv(22, 1, m_specialCube.GetPosX());

	if (MyGL::TestForError(LogMsgType::cFatalError, "glUniform3fv(): 22, Temp light failed!!!!!!!!!!"))return false;
	glUniformMatrix4fv(16, 1, GL_FALSE, &screenMat[0][0]);
	return true;
}





bool BodaciousQuest::WaterCallback(GraphicalObject * gob, glm::mat4 screenMat)
{
	//static const GLfloat tempLight[3] = { 0.0f, 1.0f, 0.0f };


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	GLint baseTexture = 20;
	//GLint reflectionMap = 25;// ShaderManager::GetShaderProgram(6)->GetUniformLocation("reflectionSampler");
	GLint normalMap = 30;//ShaderManager::GetShaderProgram(6)->GetUniformLocation("reflectionSampler");

	glUniform1i(baseTexture, 0);
	//glUniform1i(reflectionMap, 1);
	glUniform1i(normalMap, 1);


	glActiveTexture(GL_TEXTURE0);
	TextureManager::BindImageByID(gob->GetTexture());
	if (MyGL::TestForError(LogMsgType::cFatalError, "WaterCallback(): GetTexture failed"))return false;

	glActiveTexture(GL_TEXTURE1);
	TextureManager::BindImageByID(gob->GetNormalTexture());
	if (MyGL::TestForError(LogMsgType::cFatalError, "WaterCallback(): GetNormal failed"))return false;


	//glUniform1i(20 , gob->GetTexture());
	glUniformMatrix4fv(21, 1, GL_FALSE, &(gob->GetRotationMatrix() * gob->GetScaleMatrix())[0][0]);
	//23
	//	24
	glUniform3fv(23, 1, gob->GetPosX());
	glUniform3fv(24, 1, &m_camera.GetPosition()[0]);
	if (MyGL::TestForError(LogMsgType::cFatalError, "WaterCallback(): 24, Camera pos failed"))return false;

	glUniform3fv(22, 1, m_specialCube.GetPosX());

	if (MyGL::TestForError(LogMsgType::cFatalError, "WaterCallback(): 22, Temp light pos failed"))return false;
	glUniformMatrix4fv(16, 1, GL_FALSE, &screenMat[0][0]);
	return true;
}









bool BodaciousQuest::InitializeGL()
{
																																 
	//m_perspective2.SetPerspective(90.0f, 1.0f, 0.01f, 1000.0f);
	glViewport(0, 0, m_window->width(), m_window->height());

	if (!ShaderManager::Initialize()) { GameLogger::Log(LogMsgType::cFatalError, "ShaderManagerInit failed"); return false; }

	if (!ShaderManager::AddNewShader("..\\Data\\shaders\\debug.vert.shader", "..\\Data\\shaders\\debug.frag.shader")) return false;
	if (!ShaderManager::AddNewShader("..\\Data\\shaders\\play.vert.shader", "..\\Data\\shaders\\play.frag.shader")) return false;
	if (!ShaderManager::AddNewShader("..\\Data\\shaders\\texture.vert.shader", "..\\Data\\shaders\\texture.frag.shader")) return false;
	if (!ShaderManager::AddNewShader("..\\Data\\shaders\\framebuffer.vert.shader", "..\\Data\\shaders\\framebuffer.frag.shader")) return false;
	if (!ShaderManager::AddNewShader("..\\Data\\shaders\\lighting.vert.shader", "..\\Data\\shaders\\lighting.frag.shader")) return false;
	if (!ShaderManager::AddNewShader("..\\Data\\shaders\\texlighting.vert.shader", "..\\Data\\shaders\\texlighting.frag.shader")) return false;
	if (!ShaderManager::AddNewShader("..\\Data\\shaders\\water.vert.shader", "..\\Data\\shaders\\water.frag.shader")) return false;//6


	//if (!m_program.Initialize()) {
	//	GameLogger::Log(LogMsgType::cError, "BodaciousQuest::InitializeGL():m_program.Initialize() failed.");
	//	return;
	//}
	/*if (!m_program.AddVertexShader("..\\Data\\shaders\\play.vert.shader")) {
		GameLogger::Log(LogMsgType::cError, "BodaciousQuest::InitializeGL():AddVertexShader failed.");
		return;
	}
	if (!m_program.AddFragmentShader("..\\Data\\shaders\\play.frag.shader")) {
		GameLogger::Log(LogMsgType::cError, "BodaciousQuest::InitializeGL():AddFragShader failed.");
		return;
	}*/

	//if (!m_program.AddVertexShader("..\\Data\\shaders\\debug.vert.shader")) {
	//	GameLogger::Log(LogMsgType::cError, "BodaciousQuest::InitializeGL():AddVertexShader failed.");
	//	return;
	//}
	//if (!m_program.AddFragmentShader("..\\Data\\shaders\\debug.frag.shader")) {
	//	GameLogger::Log(LogMsgType::cError, "BodaciousQuest::InitializeGL():AddFragShader failed.");
	//	return;
	//}
	//if (!m_program.LinkAndUseProgram()) return;

	//uniformLocPos			= m_program2.GetUniformLocation("position");																			 
	//uniformLocScale		= m_program2.GetUniformLocation("scale");																				 



																			 
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	//if (TextureManager::LoadGameBitmap("..\\Data\\Textures\\pepper.bmp") == 0)//!TextureManager::GenFrameBuffer())
	if (!TextureManager::GenFrameBuffer())

	{
		GameLogger::Log(LogMsgType::cFatalError, "BodaciousQuest::InitializeGL(): GenFrameBuffer() failed");
		return false;
	}
	//glDepthRange(0.01f, 100.0f);
	return true;
}

void BodaciousQuest::GetPerspective()
{
	float aspecty = static_cast<float>(m_window->width()) / m_window->height();
	m_perspective.SetPerspective(m_fov, aspecty, m_zNear, m_zFar);
	m_perspective2.SetPerspective(m_fov, 1.0f, m_zNear, m_zFar);
}


void BodaciousQuest::Update(float dt)
{

	//m_readObj.SetRotationMatrix(m_camera.GetRotationMatrix());
	//m_readObj.SetPos(m_camera.GetPosition() + m_camera.GetLookVec()*10.0f);


	/*static bool increase = false;
	static float value = 0.3f;

	if (value < 0.0f)
	{
		increase = true;
		value = 0.0f;
	}
	if (value > 0.3f)
	{
		increase = false;
		value = 0.30f;
	}

	if (increase)
	{
		value += 0.3f*dt;
	}
	else
	{
		value -= 0.3f*dt;
	}

	m_window->setWindowOpacity(value);
*/
//pyramid2.SetRotationAxis(glm::vec3(0,1.0f,0));
//pyramid2.Rotate(45.0f*dt);
	if (m_carryCube) {
		m_specialCube.SetPos((m_camera.GetPosition() + (m_camera.GetLookVec()*3.0f)));
	}
	if (m_carryChicken) {
		m_chicken.SetPos((m_camera.GetPosition() + (m_camera.GetLookVec()*4.0f)));
	//	m_chicken.Rotate(45*dt);
	}
	if (m_carryDargon) {
		m_dargon.SetPos((m_camera.GetPosition() + (m_camera.GetLookVec()*4.0f)));
	}
	if (m_dargonLookat)
	{
		m_dargon.LookAt(m_camera.GetPosition());
	}

	//m_chicken.Rotate(35.0f*dt);
		cube.Rotate(90.0f*dt);
	

//MUST come before process input

	if (m_running){
		m_keyboard.Update(dt);
	if (m_paused) { return; }

	 //Rotate(45.0f*dt);
	//m_mirrorCam.Reflect(m_camera.GetLookVec());
	//m_debugCube.LookAt(m_mirrorCam.GetPosition() + m_mirrorCam.GetLookVec());
	if (m_lockOn) {
		m_texPlane.LookAt(m_camera.GetPosition());
		cube.LookAt(m_camera.GetPosition());
	}
	
	m_readObj3.Rotate(45.0f*dt * m_time);
	m_readObj2.LookAt(m_camera.GetPosition());
	//m_texPlane.SetPos(m_camera.GetPosition() + m_camera.GetLookVec() * 15.0f);
	//m_texPlane.LookAt(m_camera.GetPosition());
	//m_texPlane.LookAt( m_camera.GetPosition());
	m_time += dt;
	//if (m_paused) { return; }
	ProcessInput(dt);
	//GetAsyncKey queues inputs, had to place the pause returns after.
	//m_cubeManager.Update(dt);
	ShowFrameRate(dt);
	}
}

void BodaciousQuest::Draw()
{
	if (m_running) {

		if (m_time >= FB_DRAW_TIME)
		{
			m_time = 0;
		}
		//m_mirrorCam.Reflect(m_camera.GetPosition());
		//m_mirrorCam.GetReflectionToViewMatrix(m_camera.GetPosition());
		m_mirrorCam.LookAt(m_chicken.GetPos());
		//glFogF
		//glFogf(GL_FOG)
		//glblen
		if (fb_switch) {
			glActiveTexture(GL_TEXTURE0);

			if (!TextureManager::Draw(m_perspective2.GetPerspective(), m_mirrorCam.GetWorldToViewMatrix(), m_window->width(), m_window->height(),glm::vec4(0.5f,0.6f,0.8f,0.2f) ,glm::vec4(0.5f, 0.6f, 0.8f, 1.0f)))
			{
				GameLogger::Log(LogMsgType::cFatalError, "Draw failed!");
				Shutdown();
				return;
			}
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		//glm::mat4 mat =  glm::mat4();//m_camera.GetWorldToViewMatrix();
		////glUniformMatrix4fv(16, 1, GL_FALSE, &( glm::translate(glm::mat4(),m_mirrorCam.GetPosition()) *m_camera.GetWorldToViewMatrix())[0][0]);
		//glLineWidth(1.0);
		//glColor3f(1.0, 0.0, 0.0);
		//glBegin(GL_LINES);
		//glm::vec3 c = glm::vec3(mat * glm::vec4(0,0,0,0.0f));//m_camera.GetPosition();
		//glm::vec3 ce = glm::vec3(mat * glm::vec4((m_mirrorCam.GetLookVec() * 2.0f), 0.0f));//m_camera.GetPosition() + glm::vec3//(m_mirrorCam.GetLookVec() * 2.0f);
		//glVertex3f(c.x, c.y, c.z);
		//glVertex3f(ce.x, ce.y, ce.z);
		//glEnd();
		//glEnable(GL_FOG);
		//glFogf(GL_FOG_DENSITY, 3.0f);
		//glFogf(GL_FOG_START, 0.0f);
		//glFogf(GL_FOG_END, 0.002f);

		glm::mat4 cameraMat = m_camera.GetWorldToViewMatrix();
		if (!RenderEngine::Draw(m_perspective.GetPerspective(), cameraMat))
		{
			GameLogger::Log(LogMsgType::cFatalError, "Draw failed!");
			Shutdown();
			return;
		}
			//glDisable(GL_FOG);
		//glDrawLine
	}
	
}

void BodaciousQuest::ShowFrameRate(float dt)
{
	static unsigned numFrames = 0;
	static float    timeAccumulator = 0.0f;

	++numFrames;
	timeAccumulator += dt;

	if (timeAccumulator >= m_fpsInterval)
	{
		printf("FPS: %6.1f over %3.1f seconds.\n", numFrames / timeAccumulator, m_fpsInterval);
		timeAccumulator = 0;
		numFrames = 0;
	}

}

bool BodaciousQuest::ReloadConfig()
{
	return m_config->ReloadConfigVals();
}

void BodaciousQuest::UpdateCubePos()
{
	glm::vec3 newPos = glm::vec3(0, 0, 0);
	m_config->GetFloatsForKey("BodaciousQuest.LightingTest.Light.Position", 3, &newPos[0]);
	m_specialCube.SetPos(newPos);

}

void BodaciousQuest::MouseMove(QMouseEvent * e)
{
	if (m_paused) { return; }
	static int oldX = 0;
	static int oldY = 0;
	if (e->buttons() & Qt::RightButton)
	{
		int deltaX = e->x() - oldX;
		int deltaY = e->y() - oldY;
		m_camera.MouseRotate(deltaX, deltaY);
		
		//m_mirrorCam.MouseRotate(-deltaX, deltaY);
	}

	/*if (e->buttons() & Qt::LeftButton)
	{
		m_dist += 0.01f;
	}*/
	oldX = e->x();
	oldY = e->y();

}

void BodaciousQuest::OnResizeWindow()
{
	if (m_window == nullptr) return;
	float aspect = static_cast<float>(m_window->width()) / m_window->height();


	m_perspective.SetAspect(aspect);
	//m_perspective2.SetAspect(1.0f);
	
	glViewport(0, 0, m_window->width(), m_window->height());
}

bool BodaciousQuest::GetConfigValues()
{

	//FPS
	if (!m_config->GetFloatForKey("BodaciousQuest.FpsInterval", m_fpsInterval)) return false;
	if (m_fpsInterval > 5.0f)
	{
		m_fpsInterval = 5.0f;
	}
	if (m_fpsInterval < 0.50f)
	{
		m_fpsInterval = 0.50f;
	}



	if (!m_config->GetBoolForKey("BodaciousQuest.ShowFullScreen", m_showFullScreen, false)) return false;
	if (!m_config->GetBoolForKey("BodaciousQuest.EnableControls", m_enableControls, false)) return false;
	if (!m_config->GetBoolForKey("BodaciousQuest.CameraWalkMode", m_walk, false)) return false;
	return true;
}

bool BodaciousQuest::KeyIsDown(int vKey)
{
	return (0 != GetAsyncKeyState(vKey));
}


void BodaciousQuest::ProcessInput(float dt)
{
	
	if (m_window->hasFocus()) {

		if (m_keyboard.KeyWasReleased('X')) { Shutdown(); }

		if (m_keyboard.KeyIsDown('A')) {
			m_camera.MoveLeft(dt);
		}

		if (m_keyboard.KeyIsDown('D')) {
			m_camera.MoveRight(dt);
		}

		if (m_walk) {

			if (m_keyboard.KeyIsDown('W')) {
				m_camera.WalkForward(dt);
			}

			if (m_keyboard.KeyIsDown('S')) {
				m_camera.WalkBack(dt);
			}
		}
		else
		{
			if (m_keyboard.KeyIsDown('W')) {
				m_camera.MoveForward(dt);
			}

			if (m_keyboard.KeyIsDown('S')) {
				m_camera.MoveBack(dt);
			}
		}




		if (m_keyboard.KeyIsDown('R') || m_keyboard.KeyIsDown(VK_SPACE)) {
			m_camera.MoveUp(dt);
		}

		if (m_keyboard.KeyIsDown('F') || m_keyboard.KeyIsDown(VK_SHIFT)) {
			m_camera.MoveDown(dt);
		}

		if (m_keyboard.KeyWasPressed('0'))
		{
			if (!ReloadConfig()) { 
				Shutdown(); 
				return;
			}
		}

		if (m_enableControls) {

			if (m_keyboard.KeyWasPressed('C'))
			{
				m_texPlane.LookAt(m_camera.GetPosition());
			}

			if (m_keyboard.KeyIsDown('Q')) {
				m_camera.IncrementSpeed(-10.0f * dt);
			}

			if (m_keyboard.KeyIsDown('E')) {
				m_camera.IncrementSpeed(10.0f * dt);
			}

			if (m_keyboard.KeyWasPressed('T')) {
				m_window->setWindowOpacity(0.5f);
			}
			else if (m_keyboard.KeyWasPressed('O')) {
				m_window->setWindowOpacity(1.0f);
			}
			if (m_keyboard.KeyWasPressed('1')) {

				m_window->setWindowState(Qt::WindowFullScreen);
			}
			if (m_keyboard.KeyWasPressed('2')) {
				m_window->setWindowState(Qt::WindowNoState);
			}

			if (m_keyboard.KeyWasPressed('9'))
			{
				//m_mirrorCam.PrintCameraInfo();
				m_carryCube = !m_carryCube;
				GameLogger::Log(LogMsgType::cInfo, "Cube Position: X:%f, Y:%f, Z:%f", m_specialCube.GetPos().x, m_specialCube.GetPos().y, m_specialCube.GetPos().z);
			}

			if (m_keyboard.KeyWasPressed('V'))
			{
				m_texPlane.SetPos(m_camera.GetPosition());
				m_mirrorCam.SetPos(m_camera.GetPosition());
			}

			if (m_keyboard.KeyWasPressed('Y'))
			{
				m_grid.SetScaleMatrix(glm::scale(m_grid.GetScaleMatrix(), glm::vec3(.5f, .5f, .5f)));
			}

			if (m_keyboard.KeyWasPressed('H'))
			{
				m_grid.SetScaleMatrix(glm::scale(m_grid.GetScaleMatrix(), glm::vec3(2.0f, 2.0f, 2.0f)));
			}

		}

	}
	/*if (KeyIsDown('Y')) {
		m_camera.SetSensitivity(0.02f);
	}

	if (KeyIsDown('H')) {
		m_camera.SetSensitivity(0.015f);
	}*/
	
	//Additional processing goes here																											 
}
																				 