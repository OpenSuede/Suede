#include <tcp_listener.hpp>
#include <http_listener.hpp>
#include <http_request.hpp>
#include <http_response.hpp>
#include <websocket_frame.hpp>
#include <system_signal.hpp>
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

void listenToConnectedSocket(int socketfd)
{
	try
    {
        HTTP_Listener httpListener(socketfd);
    }
    catch (std::exception& e)
    {
		Log::LogEvent(0, e.what());
    }
}

void TCP_Listener::listenForTCPConnections()
{
    int newsockfd, portno, clilen;
    struct sockaddr_in serv_addr, cli_addr;
    string userInput = "";

    portno = 80;

    socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);

    if (socketFileDescriptor < 0){
		Log::LogEvent(0,"ERROR opening socket");
        exit(1);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = 80;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(socketFileDescriptor, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
		Log::LogEvent(0,"ERROR on binding");
        exit(1);
    }
	
	System_Signal::registerSocketUse(socketFileDescriptor); //to break out of listen once blocked if system shuts down

    while(System_Signal::exitActivated() == false){//continue until the system is ready to shut down
		Log::LogEvent(2,"Listening for new client connections...");

        listen(socketFileDescriptor,5);
        clilen = sizeof(cli_addr);

        newsockfd = accept(socketFileDescriptor, (struct sockaddr *)&cli_addr, (socklen_t *) &clilen);
        if (newsockfd < 0 && System_Signal::exitActivated() == false)
        {
			Log::LogEvent(0,"ERROR on new connection accept");
            exit(1);
        } else if(System_Signal::exitActivated() == true){
            return;
        }
		Log::LogEvent(2, "Connection established to: " + string(inet_ntoa(cli_addr.sin_addr)));
        std::thread* establishedConnectionThread = new std::thread(listenToConnectedSocket, newsockfd);
        connectedThreads.push_back(establishedConnectionThread);
    }
}

/**
 * Default constructor for TCP_Listener, starts listening
 */
TCP_Listener::TCP_Listener()
{
    listenForTCPConnections();
}

/**
 * Default destructor for TCP_Listener, close main socket
 */
TCP_Listener::~TCP_Listener()
{
    shutdown(socketFileDescriptor, 2);
}