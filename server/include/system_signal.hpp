#ifndef SYSTEM_SIGNAL_H
#define SYSTEM_SIGNAL_H

#include <stdio.h>
#include <string>
#include <set>

class System_Signal
{
private:
	static bool exitFlag;
	static std::set<int> socketFileDescriptors;
public:
	static bool exit();
	static bool exitActivated();
	static void registerSocketUse(int);
	static void unregisterSocketUse(int);
	static bool Initialize(void);
	static bool Finalize(void);
};

#endif
