#ifndef  MY_WINDOW
#define MY_WINDOW

//Kyle St.Amant
//MyWindow.h
//Class to present window etc
#include "GL\glew.h"
#pragma warning(push)  //Save state
#pragma warning(disable:4127) //disable warning
#pragma warning(disable:4100)
#include "QtOpenGL\qglwidget"
#include "Qt\qtimer.h"

class QMouseEvent;
class QApplication;
class ConfigReader;
#pragma warning(pop) //return to previous warning state


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

private slots :
		void Update();

private:
	QApplication * m_app;
	BodaciousQuest * m_game;
	ConfigReader * m_config;
	QTimer m_timer;
};

#endif //def MY_WINDOW