#include <user_input_listener.hpp>
#include <system_signal.hpp>
#include <log.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <string>
using std::string;

void User_Input_Listener::listenForUserInput()
{
	while(true){
        string input;
        std::cin >> input;
        if (input == "exit"){
			Log::LogEvent(2,"Exit command received");
			System_Signal::exit();
            return;
        }else {
			Log::LogEvent(1,"Not a valid user command");
        }
    }
}

/**
 * Default constructor for User_Input_Listener, starts listening for user input
 */
User_Input_Listener::User_Input_Listener()
{
    listenForUserInput();
}
