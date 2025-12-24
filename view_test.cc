#include "view.h"

#include <gtest/gtest.h>

TEST(View, Empty) {
  {
    View v;
    EXPECT_TRUE(v.empty());
    EXPECT_EQ(0, v.length());
  }

  {
    View v("");
    EXPECT_TRUE(v.empty());
    EXPECT_EQ(0, v.length());
  }

  {
    std::string s;
    View v(s);
    EXPECT_TRUE(v.empty());
    EXPECT_EQ(0, v.length());
  }

  {
    View v(nullptr, 0);
    EXPECT_TRUE(v.empty());
    EXPECT_EQ(0, v.length());
  }

  {
    View v(nullptr, 0, View::Direction::kReverse);
    EXPECT_TRUE(v.empty());
    EXPECT_EQ(0, v.length());
  }
}

TEST(View, Length) {
  {
    View v("foo");
    EXPECT_EQ(3, v.length());
  }

  {
    std::string s("bar");
    View v(s);
    EXPECT_EQ(3, v.length());
  }

  {
    std::string s("foobar");
    View v(s.data(), s.length());
    EXPECT_EQ(6, v.length());
  }

  {
    std::string s("foobar");
    View v(s.data(), s.length(), View::Direction::kReverse);
    EXPECT_EQ(6, v.length());
  }
}

TEST(View, Element) {
  {
    View v("foo");
    EXPECT_EQ('f', v[0]);
    EXPECT_EQ('o', v[1]);
    EXPECT_EQ('o', v[2]);
  }

  {
    std::string s("foo");
    View v(s);
    EXPECT_EQ('f', v[0]);
    EXPECT_EQ('o', v[1]);
    EXPECT_EQ('o', v[2]);
  }

  {
    std::string s("bar");
    View v(s.data(), s.length(), View::Direction::kReverse);
    EXPECT_EQ('b', v[0]);
    EXPECT_EQ('a', v[1]);
    EXPECT_EQ('r', v[2]);
  }
}

TEST(View, Iterator) {
  {
    View v;
    EXPECT_EQ(v.begin(), v.end());
  }

  {
    View v("foo");
    View::iterator it = v.begin();
    ASSERT_EQ(3, std::distance(it, v.end());

    EXPECT_NE(v.end(), it);
    EXPECT_EQ('f', *it);

    it++;
    EXPECT_NE(v.end(), it);
    EXPECT_EQ('o', *it);

    it++;
    EXPECT_NE(v.end(), it);
    EXPECT_EQ('o', *it);

    it++;
    EXPECT_EQ(v.end(), it);
  }

  {
    std::string s("bar");
    View v(s.data(), s.length(), View::Direction::kReverse);
    View::iterator it = v.begin();
    ASSERT_EQ(3, std::distance(it, v.end());

    EXPECT_NE(v.end(), it);
    EXPECT_EQ('b', *it);

    it++;
    EXPECT_NE(v.end(), it);
    EXPECT_EQ('a', *it);

    it++;
    EXPECT_NE(v.end(), it);
    EXPECT_EQ('r', *it);

    it++;
    EXPECT_EQ(v.end(), it);
  }
}
