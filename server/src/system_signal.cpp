#include <system_signal.hpp>
#include <iostream>
#include <stdio.h>
#include <set>
#include <string>
#include <log.hpp>
#include <sys/socket.h>

bool System_Signal::exitFlag;
std::set<int> System_Signal::socketFileDescriptors;

bool System_Signal::exit()
{
	System_Signal::exitFlag = true;
	std::set<int>::iterator iter;
	for (iter=socketFileDescriptors.begin(); iter != socketFileDescriptors.end(); ++iter) {
		shutdown(*iter, 2); //shut down any open socket
	}
	return true;
}

bool System_Signal::exitActivated()
{
	return exitFlag;
}

void System_Signal::registerSocketUse(int socketFileDescriptorInt)
{
	socketFileDescriptors.insert(socketFileDescriptorInt);
}

void System_Signal::unregisterSocketUse(int socketFileDescriptorInt)
{
	socketFileDescriptors.erase(socketFileDescriptorInt);
}

bool System_Signal::Initialize(void)
{
	System_Signal::exitFlag = false;
	return true;
}

bool System_Signal::Finalize(void)
{
	return true;//Currently nothing to clean up.
}
