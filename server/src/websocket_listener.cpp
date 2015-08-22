#include <websocket_listener.hpp>
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

void Websocket_Listener::listenForWebSocketFrames()
{
    unsigned char buffer[1028];
    bzero(buffer,1024);
    int n = read( socketFileDescriptor,buffer,1028);

    if (n < 0){
		Log::LogEvent(0,"ERROR reading from socket second time");
        exit(1);
    }

    /*printf("Frame Bytes result:");
        for (int i = 0; i < 1028; i++)
        {
            printf(" %02X ", buffer[i]);
        }
        printf("\n");*/

    bool hasMask = (bool) (buffer[1] & 0x80);
    if(hasMask){
		Log::LogEvent(2, "Websocket frame payload uses mask");
    }

    int payloadLength = (int) (buffer[1] & 0x7F);

    char payloadText[payloadLength + 1];
    for(int i = 0; i < payloadLength; i++){
        payloadText[i] = buffer[6 + i] ^ buffer[ i % 4 + 2];
    }

  //  WebSocket_Frame* frame = WebSocket_Frame::buildFrameFromBuffer(buffer);

	Log::LogEvent(2, "Here is the WebSocket message: " + string(payloadText));

    unsigned char webSocketResponse[payloadLength + 2];
    webSocketResponse[0] = 0x81;
    webSocketResponse[1] = payloadLength;
    for(int i = 0; i < payloadLength; i++){
        webSocketResponse[i + 2] = payloadText[i];
    }

    n = write(socketFileDescriptor, webSocketResponse, payloadLength + 2);
	Log::LogEvent(2, "Websocket echo sent");

    if (n < 0){
		Log::LogEvent(0, "ERROR writing to socket");
        exit(1);
    }
    //delete frame;
}

/**
 * Default constructor for Websocket_Listener, starts listening
 */
Websocket_Listener::Websocket_Listener(int socketfd)
{
	socketFileDescriptor = socketfd;
    listenForWebSocketFrames();
}