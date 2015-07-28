#include "log.hpp"
#include "gtest/gtest.h"

TEST(Log, Uninitialized) {
	EXPECT_FALSE(Log::TimeStamp());
	EXPECT_FALSE(Log::LogEvent(0,"Bad Msg, Uninitialized Logger"));
	EXPECT_FALSE(Log::Finalize());
}

TEST(Log, PreExisting) {
	Log::Initialize(0);
	EXPECT_FALSE(Log::Initialize(0));
}

TEST(Log, Correct) {
	EXPECT_TRUE(Log::Initialize(0));
	EXPECT_TRUE(Log::Finalize());
	EXPECT_TRUE(Log::Initialize(1));
	EXPECT_TRUE(Log::Finalize());
	EXPECT_TRUE(Log::Initialize(2));
	EXPECT_TRUE(Log::Finalize());
}
