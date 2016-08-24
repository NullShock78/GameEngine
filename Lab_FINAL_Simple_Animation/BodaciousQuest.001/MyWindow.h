#ifndef  MY_WINDOW
#define MY_WINDOW

//Kyle St.Amant
//MyWindow.h
//Class to present window etc
#include "GL\glew.h"
#pragma warning(push)  //Save state
#pragma warning(disable:4127) //disable warning
#pragma warning(disable:4100)
#pragma warning(disable:4251)
#pragma warning(disable:4800)

#include "QtOpenGL\qglwidget"
#include "Qt\qtimer.h"
#include <Qt\qevent.h>
#include "MouseComponent.h"

#pragma warning(pop) //return to previous warning state


class QMouseEvent;
class QApplication;
class ConfigReader;
class BodaciousQuest;
class MyWindow : public QGLWidget
{


Q_OBJECT

public:
	MyWindow(QApplication *app, BodaciousQuest *game, ConfigReader * config)
		:
		m_app(app),
		m_game(game),
		m_config(config)
	{}

	~MyWindow();
public:
	bool Initialize();
	bool Shutdown();

protected:
	void initializeGL() { Initialize(); }
	void mouseMoveEvent(QMouseEvent * e);
	void resizeEvent(QResizeEvent * e);
	void wheelEvent(QWheelEvent * w);
private slots :
		void Update();

private:
	QApplication * m_app;
	BodaciousQuest * m_game;
	ConfigReader * m_config;
	QTimer m_timer;

//	int m_currentMouseMoveFunc{ 0 };
//	int m_currentMouseWheelFunc{ 0 };
//	static const int MAX_FUNCS = 3;
//	std::function<void(QMouseEvent * e)> m_mouseMoveFuncs[MAX_FUNCS];
//	std::function<void(QWheelEvent * w)> m_mouseWheelFuncs[MAX_FUNCS];

//public:
//	bool AddMouseMoveCallback(std::function<void(QMouseEvent *)> func);
//	bool AddMouseWheelCallback(std::function<void(QWheelEvent *)> func);

};

#endif //def MY_WINDOW