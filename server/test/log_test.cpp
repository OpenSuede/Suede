#include <log.hpp>
/*
int main()
{
	//Log::LogEvent("bad message"); // This should fail (uninitialized logger)
	
	Log::Initialize(0);
	Log::LogEvent("[1]Should see only in logfile");
	Log::LogEvent("[2]Should also see only in logfile");
	
	//Log::Initialize(); // This should fail (pre-existing logger)
	
	Log::Finalize();
	
	//Log::Finalize(); // This should fail (uninitialized logger)
	
	// Print only to console
	Log::Initialize(1);
	Log::LogEvent("[3]Should only see in console");
	Log::Finalize;
	
	// Print to both
	Log::Initialize(2);
	Log::LogEvent("[4]Should see in both console and logfile");
	Log::Finalize;
	
	return 0;
}
*/