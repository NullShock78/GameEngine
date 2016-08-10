#include <iostream>

#include "MyFiles.h"
#include "ConfigReader.h"
#include "GameLogger.h"
#include "MyGL.h"
//supress instead of disable: don't need push/pop
#pragma warning(push)  //Save state
#pragma warning(disable:4127) //disable warning
#pragma warning(disable:4251)
#pragma warning(disable:4100)
#include "Qt\qapplication.h"
#include "BodaciousQuest.h"
#include "MyWindow.h"
#pragma warning(pop) //return to previous warning state



int main(int argc, char** argv)
{
	printf("Hello from Bodacious Quest (%s)\n", argv[0]);
	
	//TODO: change file names
	if (!GameLogger::Initialize("..\\Data\\LogFiles\\", "BodaciousQuest.log")) return 2;
	ConfigReader configReader;
	if (!configReader.Initialize("..\\Data\\BodaciousQuest.config"))
	{
		GameLogger::Shutdown();
		return 3;
	}
	

	bool showFullScreen;
	configReader.GetBoolForKey("BodaciousQuest.ShowFullScreen", showFullScreen, false); //Will remove default value eventually
	GameLogger::Log(LogMsgType::ConsoleOnly, "Show fullscreen is turned [%s].", ((showFullScreen)? "on" : "off"));

	QApplication app(argc, argv);
	BodaciousQuest game; //Todo config
	MyWindow*	 window = new MyWindow(&app, &game,&configReader);
	
	window->show();
	
	
	//app.setAttribute(Qt::AppWindowFullScreen, showFullScreen);
	int appResult = app.exec();
	
	//--------------------------Deletes----------------------
	delete window;
	//delete[] fileContents;
	//-------------------------------------------------------

	printf("Goodbye from Bodacious Quest\n");


	configReader.Shutdown();

	if (!GameLogger::Shutdown())return -2;

	return appResult;
}