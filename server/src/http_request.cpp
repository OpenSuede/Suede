#include <http_request.hpp>
#include <string>
#include <iostream>
#include <sstream>
using std::string;

/**
 * Getter for webSocketKey
 * @return webSocketKey String webSocketKey member data
 */
<<<<<<< HEAD
const string& HTTP_Request::getWebSocketKeyFieldValue() const
=======
const string& HTTP_Request::getWebSocketKey() const
>>>>>>> eaffd207ca018a3ef28fb95d2fe40bf265047661
{
	return webSocketKeyFieldValue;
}

/**
 * Setter for webSocketKey
 * @param key string object that will be set as webSocketKey
 * @return void
 */
<<<<<<< HEAD
void HTTP_Request::setWebSocketKeyFieldValue(const string& fieldValue)
{
	webSocketKeyFieldValue = fieldValue;
}

/**
 * Getter for Upgrade Field
 * @return upgradeFieldValue String upgradeFieldValue member data
 */
const string& HTTP_Request::getUpgradeFieldValue() const
{
	return upgradeFieldValue;
}

/**
 * Setter for Upgrade Field
 * @param fieldValue string object that will be set as upgradeFieldValue
 * @return void
 */
void HTTP_Request::setUpgradeFieldValue(const string& fieldValue)
{
	upgradeFieldValue = fieldValue;
=======
void HTTP_Request::setWebSocketKey(const string& key)
{
	webSocketKey = key;
>>>>>>> eaffd207ca018a3ef28fb95d2fe40bf265047661
}


/**
 * Getter for Connection Field
 * @return upgradeFieldValue String upgradeFieldValue member data
 */
const string& HTTP_Request::getConnectionFieldValue() const
{
	return connectionFieldValue;
}

/**
 * Setter for Connection Field
 * @param fieldValue string object that will be set as upgradeFieldValue
 * @return void
 */
void HTTP_Request::setConnectionFieldValue(const string& fieldValue)
{
	connectionFieldValue = fieldValue;
}

/**
 * This is a factory method that constructs HTTP_Request from a buffer
 * @param data A binary buffer that contains the raw HTTP Request
 * data directly from the network
 * @return request A HTTP_Request constructed from the binary buffer contents
 
 * Factory method that constructs HTTPrequest from following string format:
 * GET /chat HTTP/1.1
 * Host: server.example.com
 * Upgrade: websocket
 * Connection: Upgrade
 * Sec-WebSocket-Key: x3JJHMbDL1EzLkh9GBhXDw==
 * Sec-WebSocket-Protocol: chat, superchat
 * Sec-WebSocket-Version: 13
 * Origin: http://example.com
*/
HTTP_Request *HTTP_Request::buildRequestFromBuffer(unsigned const char* const data)
{
    string httpString((char*)data); // May not be a safe typecast since unsigned version may not have null terminator
	HTTP_Request *request = new HTTP_Request();
	std::istringstream stringStream(httpString);
    std::string line;
    while (std::getline(stringStream, line)) {
<<<<<<< HEAD
		if (line.find("Connection: ") == 0) {
			request->setConnectionFieldValue(line.substr(12, line.size() - 13));
		}else if (line.find("Upgrade: ") == 0) {
			request->setUpgradeFieldValue(line.substr(19, line.size() - 10));
		}else if (line.find("Sec-WebSocket-Key: ") == 0) {
			request->setWebSocketKeyFieldValue(line.substr(19, 24));
=======
		if (line.find("Sec-WebSocket-Key: ") == 0) {
			request->setWebSocketKey(line.substr(19, 24));
>>>>>>> eaffd207ca018a3ef28fb95d2fe40bf265047661
			//seems like this always work but may need to change to something like line.substr(19, line.size() - 20)
		}
    }
	return request;
}