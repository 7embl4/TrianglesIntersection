#include <iostream>
#include <Windows.h>
#include <gtest/gtest.h>
#include "Figures.h"
#include "Algorithm.h"

TEST(a, b) {
	figures::Polygon polygon;
	EXPECT_EQ(7 * 6, 42);
	EXPECT_EQ(7 + 6, 13);
	EXPECT_EQ(7 * 6, 41);
}
