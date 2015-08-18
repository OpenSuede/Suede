#include "system_signal.hpp"
#include "gtest/gtest.h"

TEST(System_Signal, Initialization) {
	System_Signal::Initialize(); // Set-up System Signals
	EXPECT_FALSE(System_Signal::exitActivated()); //System Signal's Initialize() method should set exit value to false
}