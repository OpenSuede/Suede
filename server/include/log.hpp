#ifndef SUEDE_LOG_H
#define SUEDE_LOG_H

#include <stdio.h>
#include <string>
#include <mutex>

class Log
{
	static FILE * SysLogFile;
	static FILE * TrafficLogFile;
	static bool LogToConsole;
	static bool LogTraffic;
	static time_t t;
	static struct tm * SysTime;
	static char FormattedTime[80];
	
	static const char S_LogFileName[128]; // This will be replaced with a config file variable eventually
	static const char T_LogFileName[128]; // This will be replaced with a config file variable eventually
	static std::mutex AccessLog;
	static std::mutex Logging;
	static std::mutex Clock;
	
	public:
	static int ERROR;
	static int WARN;
	static int DEBUG;
	static int TRAFFIC;
	
	static char * TimeStamp(void);
	static bool Initialize(void);
	static bool Initialize(int);
	static bool LogEvent(int, const char *);
	static bool LogEvent(int, std::string);
	static bool Finalize(void);
};

#endif
