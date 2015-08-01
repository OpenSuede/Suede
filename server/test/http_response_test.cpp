#include "http_response.hpp"
#include "gtest/gtest.h"
#include "string"


TEST(HTTP_Response, Base64_Basic) {
	char* outBuffer = NULL;
	unsigned char inputBinary[20] = "RWE%R$#FSDAADfFGDFQ";
	HTTP_Response::base64(inputBinary, 19, &outBuffer);
	string output(outBuffer);
	EXPECT_EQ("UldFJVIkI0ZTREFBRGZGR0RGUQ==", output);
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Tests as defined in RFC4648i sec. 10. Test Vectors: Base64 encoding
* 	        https://tools.ietf.org/html/rfc4648#section-10
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

TEST(HTTP_Response, Base64_RFC4648_TestVector1) {
	char* outBuffer = NULL;
    const int strLen= 0;
	unsigned char* inputBinary = (unsigned char*)"";
	HTTP_Response::base64(inputBinary, strLen, &outBuffer);
	string output(outBuffer);
	EXPECT_EQ("", output);
}

TEST(HTTP_Response, Base64_RFC4648_TestVector2) {
	char* outBuffer = NULL;
	const int strLen = 1;
	unsigned char* inputBinary = (unsigned char*)"f";
	HTTP_Response::base64(inputBinary, strLen, &outBuffer);
	string output(outBuffer);
	EXPECT_EQ("Zg==", output);
}

TEST(HTTP_Response, Base64_RFC4648_TestVector3) {
	char* outBuffer = NULL;
    const int strLen = 2;
	unsigned char* inputBinary = (unsigned char*)"fo";
	HTTP_Response::base64(inputBinary, strLen, &outBuffer);
	string output(outBuffer);
	EXPECT_EQ("Zm8=", output);
}

TEST(HTTP_Response, Base64_RFC4648_TestVector4) {
	char* outBuffer = NULL;
	const int strLen = 3;
	unsigned char* inputBinary = (unsigned char*)"foo";
	HTTP_Response::base64(inputBinary, strLen, &outBuffer);
	string output(outBuffer);
	EXPECT_EQ("Zm9v", output);
}

TEST(HTTP_Response, Base64_RFC4648_TestVector5) {
	char* outBuffer = NULL;
	const int strLen = 4;
	unsigned char* inputBinary = (unsigned char*)"foob";
	HTTP_Response::base64(inputBinary, strLen, &outBuffer);
	string output(outBuffer);
	EXPECT_EQ("Zm9vYg==", output);
}

TEST(HTTP_Response, Base64_RFC4648_TestVector6) {
	char* outBuffer = NULL;
	const int strLen = 5;
	unsigned char* inputBinary = (unsigned char*)"fooba";
	HTTP_Response::base64(inputBinary, strLen, &outBuffer);
	string output(outBuffer);
	EXPECT_EQ("Zm9vYmE=", output);
}
TEST(HTTP_Response, Base64_RFC4648_TestVector7) {
	char* outBuffer = NULL;
	const int strLen = 6;
	unsigned char* inputBinary = (unsigned char*)"foobar";
	HTTP_Response::base64(inputBinary, strLen, &outBuffer);
	string output(outBuffer);
	EXPECT_EQ("Zm9vYmFy", output);
}

