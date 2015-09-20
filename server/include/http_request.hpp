#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H
#include <string>
using std::string;

class HTTP_Request
{
private:
    string method;
    string resourceRequested;
    string hostFieldValue;
    string upgradeFieldValue;
    string connectionFieldValue;
    string webSocketKeyFieldValue;
    string webSocketProtocolFieldValue;
    string webSocketVersionFieldValue;
    string originFieldValue;
public:
    const string& getWebSocketKeyFieldValue() const;
    void setWebSocketKeyFieldValue(const string&);
	const string& getUpgradeFieldValue() const;
    void setUpgradeFieldValue(const string&);
	const string& getConnectionFieldValue() const;
    void setConnectionFieldValue(const string&);
    static HTTP_Request* buildRequestFromBuffer(unsigned const char* const); // Factory Method
};

#endif