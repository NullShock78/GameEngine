#include "MouseComponent.h"

#include "GameLogger.h"


int MouseComponent::m_oldX;// { 0 };
int MouseComponent::m_oldY;//{ 0 };
int MouseComponent::m_x;//{ 0 };
int MouseComponent::m_y;//{ 0 };
int MouseComponent::m_dx;//{ 0 };
int MouseComponent::m_dy;//{ 0 };
bool MouseComponent::m_leftPushed;// { false 
bool MouseComponent::m_leftHeld;//{ false };
bool MouseComponent::m_leftUp;//{ false };
bool MouseComponent::m_leftReleased;//{ false
bool MouseComponent::m_rightPushed;//{ false 
bool MouseComponent::m_rightHeld;//{ false };
bool MouseComponent::m_rightReleased;//{ fals
bool MouseComponent::m_rightUp;//{ false };
int	MouseComponent::m_deltaWheelin;
int	MouseComponent::m_deltaWheelout;


void MouseComponent::ClearBools()
{
	m_leftPushed = false;
	//m_leftHeld = false;
	m_leftReleased = false;
	m_rightPushed = false;
	//m_rightHeld = false;
	m_rightReleased = false;

	m_leftUp = false;
	m_rightUp = false;

}
void MouseComponent::MouseMove(QMouseEvent * e)
{
	
		if (e->buttons() & Qt::LeftButton) {
			//m_leftPushed = true;
			m_leftHeld = true;
		}
		else
		{
			m_leftHeld = false;
		}

		if (e->buttons() & Qt::RightButton)
		{
			//m_rightPushed = true;
			m_rightHeld = true;
		}
		else
		{
			m_rightHeld = false;
		}
	
		
	
		//if (e->buttons() & Qt::LeftButton) {
		//	//m_leftUp = true;
		//	//m_leftPushed = false;
		//	
		//}
		//else if (e->buttons() & Qt::RightButton) {
		//	//m_rightUp = true;
		//	//m_rightPushed = false;
		//	m_rightHeld = false;
		//}
	
	
	////static int oldX = 0;
	////static int oldY = 0;
	//if (e->buttons() & Qt::RightButton)
	//{
	//	m_dx =(e->x() - m_oldX);
	//	m_dy =(e->y() - m_oldY);
	//}

	//
	//m_oldX = e->x();
	//m_oldY = e->y();
}

void MouseComponent::MouseWheel(QWheelEvent * w)
{
	//printf("wheel: %d\n", w->delta());
	if (m_deltaWheelin == 0) {
		m_deltaWheelin = w->delta();
	}
}

bool MouseComponent::Initialize()
{

	QPoint p = QCursor::pos();
	m_x = p.x();
	m_y = p.y();
	m_oldX = m_x;
	m_oldY = m_y;

	m_dx = 0;
	m_dy = 0;

	m_leftPushed = false;
	m_leftHeld = false;
	m_leftUp = false;
	m_leftReleased = false;
	m_rightPushed = false;
	m_rightHeld = false;
	m_rightReleased = false;
	m_rightUp = false;


	return true;
}

bool MouseComponent::Update(float /*dt*/)
{

	//m_movement->AddYaw  (m_dx  * dt);
	//m_movement->AddPitch(m_dy  * dt);

	

	m_deltaWheelout = m_deltaWheelin;
	m_deltaWheelin = 0;

	m_oldX = m_x;
	m_oldY = m_y;
	
	m_x = QCursor::pos().x();
	m_y = QCursor::pos().y();

	

	m_dx = m_x - m_oldX;
	m_dy = m_y - m_oldY;

	
		//m_movement->AddPitch(m_dy);
		//m_movement->AddYaw(m_dx);
	
	//ClearBools();
	
	return true;
}

//Does nothing yet
bool MouseComponent::GetButtonPushed(int button)
{
	if(button == 1)return m_leftPushed;
	if (button == 2)return m_rightPushed;
	return false;
	
}
//Does nothing yet
bool MouseComponent::GetButtonHeld(int button)
{
	if (button == 1)return m_leftHeld;
	if (button == 2)return m_rightHeld;
	return false;
}

//Does nothing yet
bool MouseComponent::GetButtonReleased(int button)
{
	if (button == 1)return m_leftReleased;
	if (button == 2)return m_rightReleased;
	return false;

}

//Does nothing yet
bool MouseComponent::GetButtonUp(int button)
{
	if (button == 1)return m_leftUp;
	if (button == 2)return m_rightUp;
	return false;
}

int MouseComponent::GetDeltaWheel()
{
	return m_deltaWheelout/120;
}

int MouseComponent::GetDX(bool right)
{
	if (right && m_rightHeld)
	{
		return m_dx;
	}
	else if (!right && m_leftHeld)
	{
		return m_dx;
	}
	else
	{
		return 0;
	}

}

int MouseComponent::GetDY(bool right)
{
	if (right && m_rightHeld)
	{
		return m_dy;
	}
	else if (!right && m_leftHeld)
	{
		return m_dy;
	}
	else
	{
		return 0;
	}
}

//bool MouseComponent::AddToMouseCallback(MyWindow * window)
//{
//	return (window->AddMouseMoveCallback(std::bind(&MouseComponent::MouseMove, this)) && window->AddMouseWheelCallback(std::bind(&MouseComponent::MouseWheel, this)));
//}
