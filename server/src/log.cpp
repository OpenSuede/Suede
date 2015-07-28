#include <iostream>
#include <stdio.h>
#include <ctime>
#include <mutex>
#include <log.hpp>

FILE * Log::LogFile = NULL;
bool Log::LogToConsole = false;

std::mutex AccessLog;
std::mutex Logging;

void Log::Initialize(void)
{
	// Default initialization to type 0 (log to file)
	
	Logging.lock();
	LogFile = fopen("LOGFILE", "a");
	LogToConsole = false;
}

void Log::Initialize(int type)
{
	// Type 0: log to file || Type 1: log to console || Type 2: log to file and console
	
	Logging.lock();
	switch(type) {
	case 0:
		LogFile = fopen("LOGFILE", "a");
		LogToConsole = false;
		fprintf(LogFile, "Logging Initialized (File Only)\n");
		break;
	case 1:
		LogToConsole = true;
		std::cerr << "Logging Initialized (Console Only)" << std::endl;
		break;
	case 2:
		LogFile = fopen("LOGFILE", "a");	
		LogToConsole = true;
		std::cerr << "Logging Initialized (Console and File)" << std::endl;
		fprintf(LogFile, "Logging Initialized (Console and File)\n");
		break;
	}
}

void Log::LogEvent(const char * Msg)
{
	AccessLog.lock();
	
	if (LogToConsole)
	{
		std::cerr << Msg << std::endl;
	}
	
	if (LogFile != NULL)
	{
		fprintf(LogFile,"%s\n", Msg);
	}
	AccessLog.unlock();
}

void Log::Finalize(void)
{
	if (LogFile != NULL)
	{
		fprintf(LogFile, "\n");
		fclose(LogFile);
	}
	
	if (LogToConsole)
	{
		LogToConsole = false;
	}
	
	Logging.unlock();
}
