#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Order.hpp>

using namespace TechnicalTest;
using namespace std::string_view_literals;

TEST(OrderModelTests, ModelOrder)
{
  Order order("OrderId1", "SecurityId1", "Buy", 1'000, "Johan123", "Coderio");
  EXPECT_EQ(order.OrderId(), "OrderId1"sv);
  EXPECT_EQ(order.SecurityId(), "SecurityId1"sv);
  EXPECT_EQ(order.Side(), "Buy"sv);
  EXPECT_EQ(order.Qty(), 1'000);
  EXPECT_EQ(order.User(), "Johan123"sv);
  EXPECT_EQ(order.Company(), "Coderio"sv);
}

TEST(OrderModelTests, MoveValue)
{
  Order order1("OrderId1", "SecurityId1", "Buy", 1'000, "Johan123", "Coderio");
  EXPECT_EQ(order1.OrderId(), "OrderId1"sv);
  EXPECT_EQ(order1.SecurityId(), "SecurityId1"sv);
  EXPECT_EQ(order1.Side(), "Buy"sv);
  EXPECT_EQ(order1.Qty(), 1'000);
  EXPECT_EQ(order1.User(), "Johan123"sv);
  EXPECT_EQ(order1.Company(), "Coderio"sv);

  Order order2 = std::move(order1);
  EXPECT_EQ(order2.OrderId(), "OrderId1"sv);
  EXPECT_EQ(order2.SecurityId(), "SecurityId1"sv);
  EXPECT_EQ(order2.Side(), "Buy"sv);
  EXPECT_EQ(order2.Qty(), 1'000);
  EXPECT_EQ(order2.User(), "Johan123"sv);
  EXPECT_EQ(order2.Company(), "Coderio"sv);

  EXPECT_EQ(order1.OrderId(), ""sv);
  EXPECT_EQ(order1.SecurityId(), ""sv);
  EXPECT_EQ(order1.Side(), ""sv);
  EXPECT_EQ(order1.Qty(), 1'000);
  EXPECT_EQ(order1.User(), ""sv);
  EXPECT_EQ(order1.Company(), ""sv);

  order1 = std::move(order2);
  EXPECT_EQ(order1.OrderId(), "OrderId1"sv);
  EXPECT_EQ(order1.SecurityId(), "SecurityId1"sv);
  EXPECT_EQ(order1.Side(), "Buy"sv);
  EXPECT_EQ(order1.Qty(), 1'000);
  EXPECT_EQ(order1.User(), "Johan123"sv);
  EXPECT_EQ(order1.Company(), "Coderio"sv);

  EXPECT_EQ(order2.OrderId(), ""sv);
  EXPECT_EQ(order2.SecurityId(), ""sv);
  EXPECT_EQ(order2.Side(), ""sv);
  EXPECT_EQ(order2.Qty(), 1'000);
  EXPECT_EQ(order2.User(), ""sv);
  EXPECT_EQ(order2.Company(), ""sv);
}