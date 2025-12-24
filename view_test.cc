#include "view.h"

#include <algorithm>

#include "gtest/gtest.h"

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

TEST(View, Equals) {
  {
    View v1, v2;
    EXPECT_EQ(v1, v2);
  }

  {
    string s("foo");
    View v1, v2(s.data(), 0);
    EXPECT_EQ(v1, v2);
  }

  {
    View v1("foo"), v2("foo");
    EXPECT_EQ(v1, v2);
  }

  {
    std::string s1("foo"), s2("foo");
    View v1(s1), v2(s2);
    EXPECT_EQ(v1, v2);
  }

  {
    std::string s("foo");
    View v1(s), v2(s);
    EXPECT_EQ(v1, v2);
  }

  {
    std::string s("foo");
    View v1(s), v2("foo");
    EXPECT_EQ(v1, v2);
  }

  {
    View v1("foo"), v2("bar");
    EXPECT_FALSE(v1 == v2);
  }

  {
    std::string s1("foo"), s2("bar");
    View v1(s1), v2(s2);
    EXPECT_FALSE(v1 == v2);
  }

  {
    std::string s("foo");
    View v1(s), v2("bar");
    EXPECT_FALSE(v1 == v2);
  }

  {
    View v("foo");
    EXPECT_EQ(v, "foo");
    EXPECT_FALSE(v == "bar");
  }

  {
    View v1, v2("foo");
    EXPECT_FALSE(v1 == v2);
  }

  {
    std::string s("foo");
    View v1, v2(s);
    EXPECT_FALSE(v1 == v2);
  }
}

TEST(View, Reverse) {
  {
    View v;
    EXPECT_TRUE(v.reverse().empty());
  }

  {
    View v("oo");
    EXPECT_EQ(v, v.reverse());
  }

  {
    View v("foo");
    EXPECT_FALSE(v == v.reverse());
    EXPECT_EQ("oof", v.reverse());
    EXPECT_EQ(v.reverse(), v.reverse());
    EXPECT_EQ(v, v.reverse().reverse());
  }

  {
    View v1("bar"), v2("bar");
    EXPECT_EQ(v1.reverse(), v2.reverse());
  }
}
