#include <tcp_listener.hpp>
#include <user_input_listener.hpp>
#include <log.hpp>
#include <system_signal.hpp>
#include <iostream>
#include <exception>
#include <thread>

/**
 * Application Main function. Creates and starts TCP_Listener. Main also sets up and finalizes logger and system signals.
 * @param argc number of arguments passed into application
 * @param argv array of character arrays, each character array is a
 * parameter passed into application
 * @return status Application exit status
 */
int main( int argc, char *argv[] )
{
	System_Signal::Initialize(); // Set-up System Signals
	Log::Initialize(2); // Set-up Log for Application only once
	Log::LogEvent(2,"Starting Suede Server");
	
	std::thread inputListenerThread([](){User_Input_Listener();});//Start listener input on separate thread
	
    try
    {
        TCP_Listener listener; //Start listening for connections, blocks until system exit or failure
    }
    catch (std::exception& e)
    {
		Log::LogEvent(0, e.what()); // System failure occurred
    }
	
	inputListenerThread.join(); // Rejoin the user input listener thread before completing system exit
	
	Log::LogEvent(2,"Shutting Down Suede Server");
	Log::Finalize(); // Finalize Log for Application only once
	System_Signal::Finalize(); // Clean-up any System Signals
    return 0;
}