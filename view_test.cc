#include "view.h"

#include <gtest/gtest.h>

TEST(View, Empty) {
  View v;

  EXPECT_TRUE(v.empty());
}
