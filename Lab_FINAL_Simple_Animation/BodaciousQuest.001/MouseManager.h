#ifndef  MOUSE_MANAGER_H
#define MOUSE_MANAGER_H

#pragma warning(push)  																												 
#pragma warning(disable:4201) 	
#pragma warning(disable:4127)
#pragma warning(disable:4251)	
#include <QtGui\qmouseevent>
#pragma warning(pop)

#include <functional>

class MouseManager
{
private:
	
	static const int MAX_FUNCS = 50;
	static std::function <void(int dx, int dy)> m_updateFuncs[MAX_FUNCS];
	static int m_currentFunc;

public:
	static bool Initialize();

	static bool AddCallback(std::function <void(int dx, int dy)> func);

	static void MouseMove(QMouseEvent * e);

};

#endif //MOUSE_MANAGER