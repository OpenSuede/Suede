#ifndef SUEDE_LOG_H
#define SUEDE_LOG_H

#include <stdio.h>
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
	static bool Initialize(void);
	static bool Initialize(int);
	static bool LogEvent(int, const char *);
	static bool Finalize(void);
};

#endif
