#include "MyFiles.h"
#include <fstream>
#include "GameLogger.h"



char * MyFiles::ReadFileIntoString(const char * const filename)
{
	//TODO: log errors
	std::ifstream filestream;
	filestream.open(filename);
	if (!filestream.good()) {
		GameLogger::Log(LogMsgType::cError, "MyFiles::ReadFileIntoString() The file did not open properly: \n\t[%s]", filename);
		filestream.close();
		return nullptr;
	}
	std::filebuf * filebuffPtr = filestream.rdbuf();
	auto filesize = filebuffPtr->pubseekoff(0, filestream.end);
	long bufflen = 1 + static_cast<long>(filesize);
	if(bufflen <= 0)
	{
		GameLogger::Log(LogMsgType::cError, "MyFiles::ReadFileIntoString() was unable to seek to the end of file [%s]", filename);
		filestream.close();
		return nullptr;
	}

	GameLogger::Log(LogMsgType::Debug, "File [%s] Opened successfully! Buffer Length:[%d]", filename, bufflen);

	if (bufflen == 1) {
		GameLogger::Log(LogMsgType::cWarning, "File [%s] is empty.", filename);
	}

	
	char * returnBuff = new char[bufflen] {0};

	filebuffPtr->pubseekpos(0);
	
	filebuffPtr->sgetn(returnBuff, bufflen);
	
	filestream.close();
	
	if (bufflen < 900) {
		//YOU FORGOT THE CHARS HERE, IN THE LOG BUFFER
		GameLogger::Log(LogMsgType::Debug, "Shader file [%s] contents:\n//BEGIN\n%s\n//END\n", filename, returnBuff);
	}
	else
	{
		GameLogger::Log(LogMsgType::cDebug, "Shader file [%s] is too big to display contents.", filename);
	}
	
	return returnBuff;
}
