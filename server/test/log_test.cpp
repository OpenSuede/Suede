#include "log.hpp"
#include "gtest/gtest.h"

TEST(Log, Uninitialized) {
	EXPECT_FALSE(Log::LogEvent(0,"Bad Msg, Uninitialized Logger"));
	EXPECT_FALSE(Log::Finalize());
}

TEST(Log, PreExisting) {
	Log::Initialize(0);
	EXPECT_FALSE(Log::Initialize(0));
	Log::Finalize();
}

TEST(Log, Correct) {
	EXPECT_TRUE(Log::Initialize(0));
	EXPECT_TRUE(Log::LogEvent(0,"This should work"));
	EXPECT_TRUE(Log::LogEvent(1,"This should work"));
	EXPECT_TRUE(Log::LogEvent(2,"This should work"));
	EXPECT_TRUE(Log::LogEvent(3,"This should work"));
	EXPECT_TRUE(Log::Finalize());
	
	EXPECT_TRUE(Log::Initialize(1));
	EXPECT_TRUE(Log::LogEvent(0,"This should work"));
	EXPECT_TRUE(Log::LogEvent(1,"This should work"));
	EXPECT_TRUE(Log::LogEvent(2,"This should work"));
	EXPECT_TRUE(Log::LogEvent(3,"This should work"));
	EXPECT_TRUE(Log::Finalize());
	
	EXPECT_TRUE(Log::Initialize(2));
	EXPECT_TRUE(Log::LogEvent(0,"This should work"));
	EXPECT_TRUE(Log::LogEvent(1,"This should work"));
	EXPECT_TRUE(Log::LogEvent(2,"This should work"));
	EXPECT_TRUE(Log::LogEvent(3,"This should work"));
	EXPECT_TRUE(Log::Finalize());
}
