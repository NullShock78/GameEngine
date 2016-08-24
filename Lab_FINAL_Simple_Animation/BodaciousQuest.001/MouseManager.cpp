#include "MouseManager.h"
#include "GameLogger.h"
const int MouseManager::MAX_FUNCS;
std::function <void(int dx, int dy)> MouseManager::m_updateFuncs[MAX_FUNCS];
int MouseManager::m_currentFunc;

bool MouseManager::Initialize()
{
	return true;
}

bool MouseManager::AddCallback(std::function<void(int dx, int dy)> func)
{
	if (m_currentFunc >= MAX_FUNCS)
	{
		GameLogger::Log(LogMsgType::cFatalError, "MouseManager::AddCallback(): m_updateFuncs is full[%d]/[%d]", m_currentFunc, MAX_FUNCS);
		return false;
	}
	m_updateFuncs[m_currentFunc] = func;
	++m_currentFunc;
	return true;
}

void MouseManager::MouseMove(QMouseEvent * /*e*/)
{

	/*static int oldX = 0;
	static int oldY = 0;
	if (e->buttons() & Qt::RightButton)
	{
		int deltaX = e->x() - oldX;
		int deltaY = e->y() - oldY;
	}*/

	/*for (int j = 0; j < m_currentFunc; ++j)
	{
		m_updateFuncs[m_currentFunc];
	}*/

	/*if (e->buttons() & Qt::LeftButton)
	{
	m_dist += 0.01f;
	}*/
	//oldX = e->x();
	//oldY = e->y();

}