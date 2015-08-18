#ifndef WEBSOCKET_LISTENER_H
#define WEBSOCKET_LISTENER_H
#include <string>
#include <thread>
#include <vector>
using std::string;

class Websocket_Listener
{
private:
	int socketFileDescriptor;
	void listenForWebSocketFrames();
public:
    Websocket_Listener(int);
};

#endif