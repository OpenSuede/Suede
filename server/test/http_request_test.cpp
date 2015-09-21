#include <http_request.hpp>
#include "gtest/gtest.h"
#include "string"

TEST(HTTP_Request, MethodGetSet) {
	HTTP_Request request;
	request.setMethod("GET");
	EXPECT_EQ("GET", request.getMethod());
	request.setMethod("POST");
	EXPECT_EQ("POST", request.getMethod());
}

TEST(HTTP_Request, ValidCheckSet) {
	HTTP_Request request;
	request.setValid(true);
	EXPECT_TRUE(request.isValid());
	request.setValid(false);
	EXPECT_FALSE(request.isValid());
}

TEST(HTTP_Request, ResourcePathGetSet) {
	HTTP_Request request;
	request.setResourcePath("test");
	EXPECT_EQ("test", request.getResourcePath());
}

TEST(HTTP_Request, ProtocolVersionGetSet) {
	HTTP_Request request;
	request.setProtocolVersion("HTTP/1.1");
	EXPECT_EQ("HTTP/1.1", request.getProtocolVersion());
}