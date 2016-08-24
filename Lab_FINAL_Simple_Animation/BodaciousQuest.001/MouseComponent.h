#ifndef  MOUSE_COMPONENT_H
#define MOUSE_COMPONENT_H


//Kyle St.Amant
//8/15/2016
//description here
#include "Component.h"

#pragma warning(push)  																												 
#pragma warning(disable:4201) 	
#pragma warning(disable:4127)
#pragma warning(disable:4251)	
#include <QtGui\qmouseevent>
#include <QtGui\qcursor.h>

//#include <Qt\qcursor.h>
//#include <QtGui\qevent.h>
#pragma warning(pop)

//class MyWindow;

class MovementComponent;

class MouseComponent : public Component
{
//public:
//	bool AddToMouseCallback(MyWindow * window);

private:
	
	//Todo: grab for member vars?
	static int m_oldX;// { 0 };
	static int m_oldY;//{ 0 };
	
	static int m_x;//{ 0 };
	static int m_y;//{ 0 };
	 
	static int m_dx;//{ 0 };
	static int m_dy;//{ 0 };
	 
	 
	 
	static bool m_leftPushed;// { false };
	static bool m_leftHeld;//{ false };
	static bool m_leftUp;//{ false };
	static bool m_leftReleased;//{ false };
	static bool m_rightPushed;//{ false };
	static bool m_rightHeld;//{ false };
	static bool m_rightReleased;//{ false };
	static bool m_rightUp;//{ false };

	static void ClearBools();

	static float m_oldWheelPos;
	static float m_newWheelPos;
	static int	 m_deltaWheelin;
	static int	 m_deltaWheelout;

	//std::function<void(int,int)> m_callbacks
public:
	static void MouseMove(QMouseEvent * e);
	static void MouseWheel(QWheelEvent * w);

	bool Initialize();
	bool Update(float dt);
	bool GetButtonPushed(int button);
	bool GetButtonHeld(int button);
	bool GetButtonReleased(int button);
	bool GetButtonUp(int button);
	int GetDeltaWheel();
	int GetDX(bool right = true);
	int GetDY(bool right = true);
	


};


#endif //def MOUSE_COMPONENT_H




