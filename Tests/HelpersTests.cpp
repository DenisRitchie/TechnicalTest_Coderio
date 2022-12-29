#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>
#include <string_view>
#include <Helpers.hpp>

using namespace TechnicalTest;

TEST(HelpersTests, StringEquals)
{
  std::string_view text1 = "Text Example";
  std::string_view text2 = "text example";
  std::string_view text3 = "TEXT EXAMPLE";

  EXPECT_TRUE(StringEquals(text1, text2));
  EXPECT_TRUE(StringEquals(text1, text3));
  EXPECT_TRUE(StringEquals(text2, text3));

  std::string text4 = "Hello World?";
  std::string text5 = "Hello World!";

  EXPECT_FALSE(StringEquals(text4, text5));
}

TEST(HelpersTests, StringCompareIgnoreCase)
{
  std::string_view text1 = "Text Example";
  std::string_view text2 = "text example";
  std::string_view text3 = "TEXT EXAMPLE";

  EXPECT_EQ(StringCompareIgnoreCase(text1, text2), 0);
  EXPECT_EQ(StringCompareIgnoreCase(text1, text3), 0);
  EXPECT_EQ(StringCompareIgnoreCase(text2, text3), 0);

  std::string text4 = "Hello World?";
  std::string text5 = "Hello World!";

  EXPECT_NE(StringCompareIgnoreCase(text4, text5), 0);
  EXPECT_GT(StringCompareIgnoreCase(text4, text5), 0);
  EXPECT_LT(StringCompareIgnoreCase(text5, text4), 0);
}
