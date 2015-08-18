#ifndef HTTP_LISTENER_H
#define HTTP_LISTENER_H
#include <string>
#include <thread>
#include <vector>
using std::string;

class HTTP_Listener
{
private:
	int socketFileDescriptor;
	void listenForHTTPRequests();
public:
    HTTP_Listener(int);
};

#endif