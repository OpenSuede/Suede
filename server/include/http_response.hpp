#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H
#include <http_request.hpp>
#include <string>
using std::string;

class HTTP_Response
{
private:
	string method;
	string resourceRequested;
	string host;
	string upgrade;
	string connection;
	string webSocketKey;
	string webSocketProtocol;
	string webSocketVersion;
	string origin;
	string responseString; // temporary
	static string generateWebSocketAcceptVal(const string&);
public:
	static void base64(unsigned char const*, int, char**);
	const string& toString() const;
	void setResponseString(const string&); // temporary
	static HTTP_Response* buildResponseToRequest(const HTTP_Request *); // Factory Method
};

#endif