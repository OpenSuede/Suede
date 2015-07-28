#ifndef SUEDE_LOG_H_
#define SUEDE_LOG_H_

#include <stdio.h>
#include <ctime>
#include <string>

class Log
{
	static FILE * LogFile;
	static bool LogToConsole;
	static time_t t;
	static struct tm * SysTime;
	static char FormattedTime[80];
	
	static const char LogFileName[128]; // This will be replaced with a config file variable eventually
	
	public:
	static char * TimeStamp(void);
	static void Initialize(void);
	static void Initialize(int);
	static void LogEvent(int, const char *);
	static void Finalize(void);
};

#endif // SUEDE_LOG_H_
