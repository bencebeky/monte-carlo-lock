#include <gtest.h>

TEST(View, Empty) {
  View v;
  EXPECT_TRUE(v.empty());
}
