#include <http_listener.hpp>
#include <http_request.hpp>
#include <http_response.hpp>
#include <websocket_frame.hpp>
#include <socket_connection.hpp>
#include <log.hpp>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <string>

#include <thread>
#include <iostream>
#include <arpa/inet.h>
using std::string;

int socketFileDescriptor;

void HTTP_Listener::listenForHTTPRequests()
{
    unsigned char buffer[1028];
    bzero(buffer,1028);
	int n = read( socketFileDescriptor,buffer,1028 );

	if (n < 0){
		Log::LogEvent(0,"ERROR reading from socket");
		exit(1);
	}

	Log::LogEvent(2,"Incoming HTTP message: " + string((const char*) buffer));

	HTTP_Request *request = HTTP_Request::buildRequestFromBuffer(buffer);

	HTTP_Response *response = HTTP_Response::buildResponseToRequest(request);

	string responseString = response->toString();
	n = write(socketFileDescriptor, responseString.c_str(), responseString.size());

	Log::LogEvent(2,"HTTP Response: " + responseString);

	if (n < 0){
		Log::LogEvent(0,"ERROR writing to socket");
		exit(1);
	}

	delete request;
    delete response;
}

/**
 * Default constructor for HTTP_Listener, starts listening
 */
HTTP_Listener::HTTP_Listener(int socketfd)
{
	socketFileDescriptor = socketfd;
    listenForHTTPRequests();
}