#include <iostream>
#include <stdio.h>
#include <ctime>
#include <mutex>
#include <log.hpp>
#include <string>

FILE * Log::LogFile = NULL;
bool Log::LogToConsole = false;
time_t Log::t = time(0);
struct tm * Log::SysTime = localtime(&t);
char Log::FormattedTime[80];

const char Log::LogFileName[128] = "./log/LOGFILE"; // This will eventually be replaced with a config file variable

std::mutex AccessLog;
std::mutex Logging;
std::mutex Clock;

char * Log::TimeStamp(void)
{
	Clock.lock();
	time_t t = time(0);
	struct tm * SysTime = localtime(&t);
	strftime(FormattedTime, 80, "[%m/%d/%Y] %H:%M:%S", SysTime); // THIS IS WHERE WE WILL PUT OUR TIMESTAMP FORMATTING HOOK FOR THE LOG CONFIG FILE
	Clock.unlock();
	return FormattedTime;
}

void Log::Initialize(void)
{
	// Default initialization to type 0 (log to file)
	
	Logging.lock();
	LogFile = fopen(LogFileName, "a"); // REPLACE WITH DYNAMIC CONFIG FILE HOOK
	LogToConsole = false;
}

void Log::Initialize(int type)
{
	// Type 0: log to file || Type 1: log to console || Type 2: log to file and console
	
	Logging.lock();
	switch(type) {
	case 0:
		LogFile = fopen(LogFileName, "a"); // REPLACE WITH DYNAMIC CONFIG FILE HOOK
		LogToConsole = false;
		t = time(0);
		SysTime = localtime(&t);
		fprintf(LogFile, "%s Logging Initialized (File Only)\n", TimeStamp());
		break;
	case 1:
		LogToConsole = true;
		std::cerr << "Logging Initialized (Console Only)" << std::endl;
		break;
	case 2:
		LogFile = fopen(LogFileName, "a"); // REPLACE WITH DYNAMIC CONFIG FILE HOOK
		LogToConsole = true;
		t = time(0);
		SysTime = localtime(&t);
		std::cerr << "Logging Initialized (Console and File)" << std::endl;
		fprintf(LogFile, "%s Logging Initialized (Console and File)\n", TimeStamp());
		break;
	}
}

void Log::LogEvent(int MType, const char * Msg)
{
	AccessLog.lock();
	
	// this will be replaced with config file hooks
	char const * MsgType;
	switch(MType) {
	case 0:
		MsgType = "[Error]";
		break;
	case 1:
		MsgType = "[Warning]";
		break;
	case 2:
		MsgType = "[Debug]";
		break;
	}
	
	// Simulated delay, remember to remove
	//int x=0;
	//for (int i = 0; i < 300000000; i++){ x++; }
	// Simulated delay, remember to remove
	
	if (LogToConsole)
	{
		std::cerr << MsgType << " " << Msg << std::endl;
	}
	
	if (LogFile != NULL)
	{
		t = time(0);
		SysTime = localtime(&t);
		fprintf(LogFile,"%s %s %s\n", TimeStamp(), MsgType, Msg);
	}
	AccessLog.unlock();
}

void Log::Finalize(void)
{
	t = time(0);
	if (LogFile != NULL)
	{
		fprintf(LogFile, "\n");
		fclose(LogFile);
		LogFile = NULL;
	}
	
	if (LogToConsole)
	{
		LogToConsole = false;
	}
	
	Logging.unlock();
}
