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
