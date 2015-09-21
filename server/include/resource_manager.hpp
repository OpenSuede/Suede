#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#include <socket_connection.hpp>
#include <string>
using std::string;

class Resource_Manager
{
private:
	static Socket_Connection connectionList[];
	int connectionCount;
	static bool staleRecordRemover();//checking every minute (called by initialize)
public:
	static bool Initialize(void);
	static bool Finalize(void);
	static bool registerConnection(Socket_Connection);
	static Socket_Connection[] getConnectionList();
	static int getConnectionCount();
};

#endif