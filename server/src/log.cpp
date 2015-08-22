#include <iostream>
#include <stdio.h>
#include <mutex>
#include <string>
#include <log.hpp>

// Static Variables
FILE * Log::LogFile = NULL;
bool Log::LogToConsole = false;
time_t Log::t = time(0);
struct tm * Log::SysTime = localtime(&t);
char Log::FormattedTime[80];

const char Log::LogFileName[128] = "./log/LOGFILE"; // This will eventually be replaced with a config file variable

// Thread Blocking Objects
std::mutex Log::AccessLog;
std::mutex Log::Logging;
std::mutex Log::Clock;

char * Log::TimeStamp(void)
{
	/*
	Returns a formatted timestamp string for use in logged messages.
	TimeStamp format should be set from log config file.
	*/
	
	Clock.lock();
	time_t t = time(0);
	struct tm * SysTime = localtime(&t);
	strftime(FormattedTime, 80, "[%m/%d/%Y] %H:%M:%S", SysTime); // THIS IS WHERE WE WILL PUT OUR TIMESTAMP FORMATTING HOOK FOR THE LOG CONFIG FILE
	Clock.unlock();
	return FormattedTime;
}

bool Log::Initialize(void)
{
	/*
	Default log initialization to type 0 (log to file)
	*/
	
	if ((LogFile != NULL) or (LogToConsole != false))
	{
		return false;
	}
		
	Logging.lock();
	LogFile = fopen(LogFileName, "a"); // REPLACE WITH DYNAMIC CONFIG FILE HOOK
	LogToConsole = false;
	return true;
}

bool Log::Initialize(int type)
{
	/*
	Parameterized log initialization
	Type 0: log to file
	Type 1: log to console
	Type 2: log to file and console
	*/
	
	if ((LogFile != NULL) or (LogToConsole != false))
	{
		return false;
	}
	
	Logging.lock();
	switch(type) {
	case 0:
		LogFile = fopen(LogFileName, "a"); // REPLACE WITH DYNAMIC CONFIG FILE HOOK
		LogToConsole = false;
		t = time(0);
		SysTime = localtime(&t);
		fprintf(LogFile, "%s Logging Initialized (File Only)\n", TimeStamp());
		return true;
	case 1:
		LogToConsole = true;
		std::cerr << "Logging Initialized (Console Only)" << std::endl;
		return true;
	case 2:
		LogFile = fopen(LogFileName, "a"); // REPLACE WITH DYNAMIC CONFIG FILE HOOK
		LogToConsole = true;
		t = time(0);
		SysTime = localtime(&t);
		std::cerr << "Logging Initialized (Console and File)" << std::endl;
		fprintf(LogFile, "%s Logging Initialized (Console and File)\n", TimeStamp());
		return true;
	}
}

bool Log::LogEvent(int MType, const char * Msg)
{
	/*
	Logs an event of a given type
	Type 0: Error
	Type 1: Warning
	Type 2: Debugging Message
	*/
	
	if ((LogFile == NULL) and (LogToConsole == false))
	{
		return false;
	}
	
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
	return true;
}

bool Log::LogEvent(int MType, std::string Msg)
{
	return Log::LogEvent(MType, Msg.c_str());
}

bool Log::Finalize(void)
{
	/*
	Runs log cleanup
	*/
	
	if ((LogFile == NULL) and (LogToConsole == false))
	{
		return false;
	}
	
	if (LogFile != NULL)
	{
		fclose(LogFile);
		LogFile = NULL;
	}
	
	LogToConsole = false;
	
	Logging.unlock();
	return true;
}
