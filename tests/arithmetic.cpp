#include <gtest/gtest.h>
#include <fixed_point/FixedPoint.hpp>

// Demonstrate some basic assertions.
TEST(arithmetic, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  using P = FixedPoint<uint32_t, 8>;
  EXPECT_EQ(P(10.5f), P(3.5f) + P(7.0f));
  EXPECT_EQ(P(-3.5f), P(3.5f) - P(7.0f));
  EXPECT_EQ(P(12.0f), P(3.0f) * P(4.0f));
  EXPECT_EQ(P(4.0f), P(12.0f) / P(3.0f));
}