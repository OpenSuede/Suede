#ifndef SUEDE_LOG_H_
#define SUEDE_LOG_H_

#include <stdio.h>

class Log
{
	static FILE * LogFile;
	static bool LogToConsole;
	
	public:
	static void Initialize(void);
	static void Initialize(int);
	static void LogEvent(const char *);
	static void Finalize(void);
};

#endif // SUEDE_LOG_H_
