#include "PlayerEntity.h"


//Move to build player
bool PlayerEntity::Initialize(glm::vec3 pos, glm::vec3 offset)
{
	if (!AddComponent(&m_spatial,	"spatial",	false)){
		GameLogger::Log(LogMsgType::cFatalError, "PlayerEntity::Initialize(): SpatialComponent failed to add");
		return false;
	}
	if (!AddComponent(&m_gobcomp,	"gob",		false)){
		GameLogger::Log(LogMsgType::cFatalError, "PlayerEntity::Initialize(): GobComponent failed to add");
		return false;
	}
	//BEFORE movement
	if (!AddComponent(&m_keyboard, "keyboard", false)) {
		GameLogger::Log(LogMsgType::cFatalError, "PlayerEntity::Initialize(): KeyboardComponent failed to add");
		return false;
	}

	//BEFORE movement
	if (!AddComponent(&m_mouse, "mouse", false)) {
		GameLogger::Log(LogMsgType::cFatalError, "PlayerEntity::Initialize(): MouseComponent failed to add");

		return false;
	}
	//BEFORE movement
	if (!AddComponent(&m_cam, "camera", false)) {
		GameLogger::Log(LogMsgType::cFatalError, "PlayerEntity::Initialize(): CameraComponent failed to add");

		return false;
	}

	if (!AddComponent(&m_phasor, "phasor", false)) {
		GameLogger::Log(LogMsgType::cFatalError, "PlayerEntity::Initialize(): ShootComponent failed to add");
		return false;
	}

	if (!AddComponent(&m_jump, "jump", false)) {
		GameLogger::Log(LogMsgType::cFatalError, "PlayerEntity::Initialize(): JumpComponent failed to add");

		return false;
	}




	if (!AddComponent(&m_movement,	"movement", false)) {
		GameLogger::Log(LogMsgType::cFatalError, "PlayerEntity::Initialize(): MovementComponent failed to add");

		return false;
	}
	if (!AddComponent(&m_gravity, "gravity", false)) {
		GameLogger::Log(LogMsgType::cFatalError, "PlayerEntity::Initialize(): GravityComponent failed to add");

		return false;
	}

	//INITS
	if (!m_keyboard.Initialize()) {
		GameLogger::Log(LogMsgType::cFatalError, "PlayerEntity::Initialize(): KeyboardComponent failed to initialize");
		return false;
	}
	if (!m_spatial.Init()) { 
		GameLogger::Log(LogMsgType::cFatalError, "PlayerEntity::Initialize(): SpatialComponent failed to initialize");
		return false; 
	}

	if (!m_jump.Initialize())
	{
		GameLogger::Log(LogMsgType::cFatalError, "PlayerEntity::Initialize(): JumpComponent failed to initialize");
		return false;
	}
	

	if (!m_gobcomp.Init()) {
		GameLogger::Log(LogMsgType::cFatalError, "PlayerEntity::Initialize(): GobComponent failed to initialize");
		return false;
	}
	if (!m_mouse.Init()) {
		GameLogger::Log(LogMsgType::cFatalError, "PlayerEntity::Initialize(): MouseComponent failed to initialize");
		return false;
	}
	
	if (!m_movement.Init()) {
		GameLogger::Log(LogMsgType::cFatalError, "PlayerEntity::Initialize(): MovementComponent failed to initialize");
		return false;
	}
	if (!m_cam.Initialize(glm::vec3(0.0f,0.0f,-1.0f),5.0f,1.0f,offset)) {
		GameLogger::Log(LogMsgType::cFatalError, "PlayerEntity::Initialize(): CameraComponent failed to initialize");
		return false;
	}
	if (!m_gravity.Initialize())
	{
		GameLogger::Log(LogMsgType::cFatalError, "PlayerEntity::Initialize(): GravityComponent failed to initialize");
		return false;
	}

	if (!m_phasor.Initialize())
	{
		GameLogger::Log(LogMsgType::cFatalError, "PlayerEntity::Initialize(): PhasorComponent failed to initialize");
		return false;
	}

	m_spatial.SetPos(pos);
	m_spatial.SetRoll(0);
	m_spatial.SetRotate(glm::mat4());
	m_cam.SetSensitivity(1.0f);
	m_movement.SetRotationSensitivity(1.0f);
	m_movement.LockObj(false);
	m_cam.SetOffset(-4.0f);
	m_cam.SetMouseButton(false);
	//m_gobcomp.SetScale(2.0f);
	m_gravity.SetGravity(16.8f);
	m_spatial.SetScale(2.0f);
	//if (!m_spatial.Init())return false;
	/*if (!AddComponent())return false;
	if (!AddComponent())return false;
	if (!AddComponent())return false;
	if (!AddComponent())return false;*/
	/*if (!m_keyboard.AddKey('W')) return false;
	*/
	return true;
}

glm::mat4 PlayerEntity::GetCameraMatrix()
{
	return m_cam.GetWorldToViewMatrix();
}

GraphicalObject * PlayerEntity::GetGob()
{
	return m_gobcomp.GetGob();
}

glm::vec3 PlayerEntity::GetPosition()
{
	return m_spatial.GetPos();
}

glm::vec3 PlayerEntity::GetCamPosition()
{
	return m_cam.GetPos();
}

glm::vec3 PlayerEntity::GetLookVec()
{
	return m_cam.GetViewDir();
}

bool PlayerEntity::Update(float dt)
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

	//float result = m_tester.FindWall(m_player.GetPos)

	return true;
}
const float * PlayerEntity::GetCamPos()
{
	return m_cam.GetPosPtr();
}

void PlayerEntity::SetScale(float scale)
{
	m_spatial.SetScale(scale);
}

void PlayerEntity::SetAmmo(GraphicalObject * gob)
{
	m_phasor.SetAmmo(gob);
}
//bool PlayerEntity::AddToMouseCallback(MyWindow * window)
//{
//	return m_mouse.AddToMouseCallback(window);
//	
//}

//bool PlayerEntity::Update(float dt)
//{
//for (int j = 0; j < MAX_COMPONENTS; j++)
//{
//	if (m_components[j] && m_components[j]->IsEnabled())
//	{
//		bool result = m_components[j]->Update(dt);
//		assert(result);
//	}
//}
//
//return true;
//}