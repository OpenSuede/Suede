#include <http_request.hpp>
#include <string>
#include <iostream>
#include <sstream>
using std::string;

/**
 * Getter for method
 * @return method type as string
 */
const string& HTTP_Request::getMethod() const
{
	return method;
}

/**
 * Setter for method
 * @param key string object that will be set as method
 * @return void
 */
void HTTP_Request::setMethod(const string& methodIn)
{
	method = methodIn;
}

/**
 * valid request check
 * @return request validity as a boolean
 */
const bool HTTP_Request::isValid() const
{
	return isRequestValid;
}

/**
 * Setter for isValid
 * @param request validity as a boolean
 * @return void
 */
void HTTP_Request::setValid(const bool validity)
{
	isRequestValid = validity;
}

/**
 * Getter for ResourcePath
 * @return ResourcePath type as string
 */
const string& HTTP_Request::getResourcePath() const
{
	return resourcePath;
}

/**
 * Setter for ResourcePath
 * @param key string object that will be set as ResourcePath
 * @return void
 */
void HTTP_Request::setResourcePath(const string& resource)
{
	resourcePath = resource;
}

/**
 * Getter for protocolVersion
 * @return protocolVersion type as string
 */
const string& HTTP_Request::getProtocolVersion() const
{
	return protocolVersion;
}

/**
 * Setter for protocolVersion
 * @param key string object that will be set as protocolVersion
 * @return void
 */
void HTTP_Request::setProtocolVersion(const string& version)
{
	protocolVersion = version;
}

/**
 * Getter for webSocketKey
 * @return webSocketKey String webSocketKey member data
 */
const string& HTTP_Request::getWebSocketKeyFieldValue() const
{
	return webSocketKeyFieldValue;
}

/**
 * Setter for webSocketKey
 * @param key string object that will be set as webSocketKey
 * @return void
 */
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
	request->setValid(true);
	std::istringstream stringStream(httpString);
    std::string line;
	std::getline(stringStream, line);
	if (line.find("GET") == 0) {
		request->setMethod("GET");
	}else if (line.find("POST") == 0) {
		request->setMethod("POST");
	}else if (line.find("DELETE") == 0) {
		request->setMethod("DELETE");
	}else if (line.find("PUT") == 0) {
		request->setMethod("PUT");
	}else if (line.find("HEAD") == 0) {
		request->setMethod("HEAD");
	} else {
		request->setValid(false);
	}
	
	int start = line.find(" ") + 1;
	int len = line.find(" ", start) - start;
	request->setResourcePath(line.substr(start, len));
	
	start += len;
	len = line.find("/r", start) - start;
	request->setProtocolVersion(line.substr(start, len));
	
    while (std::getline(stringStream, line)) {
		if (line.find("Connection: ") == 0) {
			request->setConnectionFieldValue(line.substr(12, line.size() - 13));
		}else if (line.find("Upgrade: ") == 0) {
			request->setUpgradeFieldValue(line.substr(19, line.size() - 10));
		}else if (line.find("Sec-WebSocket-Key: ") == 0) {
			request->setWebSocketKeyFieldValue(line.substr(19, 24));
			//seems like this always work but may need to change to something like line.substr(19, line.size() - 20)
		}
    }
	return request;
}