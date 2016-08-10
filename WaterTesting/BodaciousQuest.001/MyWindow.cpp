#include "BodaciousQuest.h"
#include "MyWindow.h"
#include "GameTime.h"
#include "GameLogger.h"
#pragma warning(push)  //Save state
#pragma warning(disable:4127) //disable warning
#pragma warning(disable:4251)
#pragma warning(disable:4100)
#include "Qt\qapplication.h"
#pragma warning(pop) //return to previous warning state

MyWindow::~MyWindow()
{
}

bool MyWindow::Initialize()
{

	GLenum initResult = glewInit();
	if (initResult != GLEW_OK)
	{
		Shutdown();
		GameLogger::Log(LogMsgType::FatalError, "Unable to initialize glew result was (%s)", initResult);
		return false;
	}

	setMouseTracking(true);
	connect(&m_timer, SIGNAL(timeout()), this, SLOT(Update()));

	
	if (!m_game->Initialize(this, m_config))

	{
		GameLogger::Log(LogMsgType::cFatalError, "MyWindow::Initialize() Failed to initialize m_game.");
		Shutdown();
		return false;
	}
		
		
		
	if (!GameTime::Initialize())
	{
		GameLogger::Log(LogMsgType::cFatalError, "MyWindow::Initialize() Failed to initialize Gametime.");

		Shutdown();
		return false;
	}

	

	m_timer.start();
	GameLogger::Log(LogMsgType::cProcess, "MyWindow::Initialize() successful!");
	
	return true;
}



bool MyWindow::Shutdown()
{
	m_app->exit();
	GameLogger::Log(LogMsgType::cProcess, "MyWindow::Shutdown() successful!");
	return true;
}

void MyWindow::mouseMoveEvent(QMouseEvent * e)
{
	m_game->MouseMove(e);
}

void MyWindow::resizeEvent(QResizeEvent * /*e*/)
{
	m_game->OnResizeWindow();

}

void MyWindow::Update()
{
	float dt = GameTime::GetLastFrameTime();

	m_game->Update(dt);
	m_game->Draw();
	this->repaint();
}