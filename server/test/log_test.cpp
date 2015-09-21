#include "log.hpp"
#include "gtest/gtest.h"

TEST(Log, Uninitialized) {
	EXPECT_FALSE(Log::LogEvent(Log::ERROR,"Bad Msg, Uninitialized Logger"));
	EXPECT_FALSE(Log::Finalize());
}

TEST(Log, PreExisting) {
	Log::Initialize(0);
	EXPECT_FALSE(Log::Initialize(0));
	Log::Finalize();
}

TEST(Log, Correct) {
	EXPECT_TRUE(Log::Initialize(0));
	EXPECT_TRUE(Log::LogEvent(Log::ERROR,"This should work"));
	EXPECT_TRUE(Log::LogEvent(Log::WARN,"This should work"));
	EXPECT_TRUE(Log::LogEvent(Log::DEBUG,"This should work"));
	EXPECT_TRUE(Log::LogEvent(Log::TRAFFIC,"This should work"));
	EXPECT_TRUE(Log::Finalize());
	
	EXPECT_TRUE(Log::Initialize(1));
	EXPECT_TRUE(Log::LogEvent(Log::ERROR,"This should work"));
	EXPECT_TRUE(Log::LogEvent(Log::WARN,"This should work"));
	EXPECT_TRUE(Log::LogEvent(Log::DEBUG,"This should work"));
	EXPECT_TRUE(Log::LogEvent(Log::TRAFFIC,"This should work"));
	EXPECT_TRUE(Log::Finalize());
	
	EXPECT_TRUE(Log::Initialize(2));
	EXPECT_TRUE(Log::LogEvent(Log::ERROR,"This should work"));
	EXPECT_TRUE(Log::LogEvent(Log::WARN,"This should work"));
	EXPECT_TRUE(Log::LogEvent(Log::DEBUG,"This should work"));
	EXPECT_TRUE(Log::LogEvent(Log::TRAFFIC,"This should work"));
	EXPECT_TRUE(Log::Finalize());
}
