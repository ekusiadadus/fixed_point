#include <gtest/gtest.h>

#include <FixedPoint.hpp>

// Demonstrate some basic assertions.
TEST(arithmetic, BasicAssertions) {
  using P = FixedPoint<uint32_t, 8>;
  EXPECT_EQ(P(10.5f), P(3.5f) + P(7.0f));
  EXPECT_EQ(P(-3.5f), P(3.5f) - P(7.0f));
  EXPECT_EQ(P(12.0f), P(3.0f) * P(4.0f));
  EXPECT_EQ(P(4.0f), P(12.0f) / P(3.0f));
}

TEST(arithmethic, addition) {
  using P = FixedPoint<uint32_t, 8>;

  EXPECT_EQ(P(10.5f), P(3.5f) + P(7.0f));
}

TEST(arithmethic, subtraction) {
  using P = FixedPoint<uint32_t, 8>;

  EXPECT_EQ(P(-3.5f), P(3.5f) - P(7.0f));
}

TEST(arithmethic, multiplication) {
  using P = FixedPoint<uint32_t, 8>;

  EXPECT_EQ(P(-24.5f), P(3.5f) * -P(7.0f));
}

TEST(arithmethic, division) {
  using P = FixedPoint<uint32_t, 8>;

  EXPECT_EQ(P(float(3.5 / 7.0)), P(3.5f) / P(7.0f));
  EXPECT_EQ(P(float(-3.5 / 7.0)), P(-3.5f) / P(7.0f));
  EXPECT_EQ(P(float(3.5 / -7.0)), P(3.5f) / -P(7.0f));
  EXPECT_EQ(P(float(-3.5 / -7.0)), P(-3.5f) / -P(7.0f));

#ifndef NDEBUG
  EXPECT_DEATH(P(1.0f) / P(0.0f), "");
#endif
}

TEST(arithmethic, division_range) {
  using P = FixedPoint<uint32_t, 12>;

  // These calculation will overflow and produce
  // wrong results without the intermediate type.
  EXPECT_EQ(P(32.0f), P(256.0f) / P(8.0f));
}