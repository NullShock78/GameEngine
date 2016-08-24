#include <iostream>
#include "ConfigReader.h"
#include "GameLogger.h"
#include "ObjConverter.h"
int main(int /*argc*/, char** argv)
{
	printf("Hello from Obj converter (%s)\n", argv[0]);

	//TODO: change file names
	if (!GameLogger::Initialize("..\\Data\\LogFiles\\", "ObjConverter.log")) return 2;
	ConfigReader configReader;
	if (!configReader.Initialize("..\\Data\\BodaciousQuest.config"))
	{
		GameLogger::Shutdown();
		return 3;
	}


	ObjConverter objConv;
	if(!objConv.InitializeAndRun(&configReader))return -4;
	//objConv.ReadFile();
	printf("Goodbye from Obj converter\n");

	//if(!objConv.ReadFile())
	if (!configReader.Shutdown()) { GameLogger::Shutdown(); return -3; }

	if (!GameLogger::Shutdown())return -2;

	return 0;
}