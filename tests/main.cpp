#include <iostream>
#include <Windows.h>
#include <gtest/gtest.h>
#include "Figures.h"

int main() {
	EXPECT_STRNE("hello", "world");
	EXPECT_EQ(7 * 6, 42);
	Sleep(50);
	return 0;
}