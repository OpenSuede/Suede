#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H
#include <string>
using std::string;

class HTTP_Request
{
private:
    string method;
	bool isRequestValid;
    string resourcePath;
	string protocolVersion;
    string hostFieldValue;
    string upgradeFieldValue;
    string connectionFieldValue;
    string webSocketKeyFieldValue;
    string webSocketProtocolFieldValue;
    string webSocketVersionFieldValue;
    string originFieldValue;
public:
	const string& getMethod() const;
    void setMethod(const string&);
	const bool isValid() const;
    void setValid(const bool);
	const string& getResourcePath() const;
    void setResourcePath(const string&);
    const string& getWebSocketKeyFieldValue() const;
	void setProtocolVersion(const string&);
    const string& getProtocolVersion() const;
    void setWebSocketKeyFieldValue(const string&);
	const string& getUpgradeFieldValue() const;
    void setUpgradeFieldValue(const string&);
	const string& getConnectionFieldValue() const;
    void setConnectionFieldValue(const string&);
    static HTTP_Request* buildRequestFromBuffer(unsigned const char* const); // Factory Method
};

#endif