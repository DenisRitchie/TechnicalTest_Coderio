#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <fstream>
#include <sstream>
#include <memory>

#include <OrderService.hpp>

#include "OrderCacheFake.hpp"

using ::testing::_;
using ::testing::AnyNumber;

using namespace TechnicalTest;
using namespace std::string_literals;
using namespace std::string_view_literals;

class OrderServiceTests : public ::testing::Test
{
  public:
    void SetUp() override
    {
      LoadContent("Data/TestData1.txt", m_TestData1);
      LoadContent("Data/TestData2.txt", m_TestData2);
      LoadContent("Data/TestData3.txt", m_TestData3);

      for ( auto&& values : m_TestData1 )
      {
        Order order{ values[0], values[1], values[2], (uint32_t)std::stoi(values[3].c_str()), values[4], values[5] };
        m_Service1.AddOrder(std::move(order));
      }

      for ( auto&& values : m_TestData2 )
      {
        Order order{ values[0], values[1], values[2], (uint32_t)std::stoi(values[3].c_str()), values[4], values[5] };
        m_Service2.AddOrder(std::move(order));
      }

      for ( auto&& values : m_TestData3 )
      {
        Order order{ values[0], values[1], values[2], (uint32_t)std::stoi(values[3].c_str()), values[4], values[5] };
        m_Service3.AddOrder(std::move(order));
      }
    }

    void TearDown() override
    {
    }

  private:
    static void LoadContent(const std::string_view file_path, std::vector<std::vector<std::string>>& output)
    {
      std::ifstream file{ file_path.data() };

      while ( !file.eof() )
      {
        std::string text;
        std::getline(file, text);

        std::istringstream       is{ std::move(text) };
        std::vector<std::string> tokens;

        while ( !is.eof() )
        {
          is >> text;
          tokens.emplace_back(std::move(text));
        }

        output.emplace_back(std::move(tokens));
      }
    }

  protected:
    std::vector<std::vector<std::string>> m_TestData1;
    std::vector<std::vector<std::string>> m_TestData2;
    std::vector<std::vector<std::string>> m_TestData3;

    // clang-format off
    OrderService m_Service1;
    OrderService m_Service2;
    OrderService m_Service3;
    // clang-format on
};

TEST_F(OrderServiceTests, AddOrder_TestData1)
{
  EXPECT_EQ(m_Service1.TotalOrders(), 13);

  for ( int32_t index = 1; index <= m_Service1.TotalOrders(); ++index )
  {
    EXPECT_NE(m_Service1.FindOrderById("OrdId"s + std::to_string(index)), std::nullopt);
  }
}

TEST_F(OrderServiceTests, AddOrder_TestData2)
{
  EXPECT_EQ(m_Service2.TotalOrders(), 11);

  for ( int32_t index = 1; index <= m_Service2.TotalOrders(); ++index )
  {
    EXPECT_NE(m_Service2.FindOrderById("OrdId"s + std::to_string(index)), std::nullopt);
  }
}

TEST_F(OrderServiceTests, AddOrder_TestData3)
{
  EXPECT_EQ(m_Service3.TotalOrders(), 8);

  for ( int32_t index = 1; index <= m_Service3.TotalOrders(); ++index )
  {
    EXPECT_TRUE(m_Service3.ExistsOrderId("OrdId"s + std::to_string(index)));
  }
}

TEST_F(OrderServiceTests, CancelOrder)
{

  EXPECT_EQ(m_Service1.TotalOrders(), 13);

  m_Service1.CancelOrder("OrdId6");

  EXPECT_EQ(m_Service1.TotalOrders(), 12);

  EXPECT_FALSE(m_Service1.ExistsOrderId("OrdId6"));
}

TEST_F(OrderServiceTests, CancelOrdersForUser)
{
  EXPECT_EQ(m_Service2.TotalOrders(), 11);

  m_Service2.CancelOrdersForUser("User2");

  EXPECT_EQ(m_Service2.TotalOrders(), 8);

  EXPECT_FALSE(m_Service2.ExistsOrderId("OrdId3"));
  EXPECT_FALSE(m_Service2.ExistsOrderId("OrdId5"));
  EXPECT_FALSE(m_Service2.ExistsOrderId("OrdId8"));
}

TEST_F(OrderServiceTests, CancelOrdersForSecurityIdWithMinimumQty)
{
  EXPECT_EQ(m_Service3.TotalOrders(), 8);

  m_Service3.CancelOrdersForSecurityIdWithMinimumQty("SecId2", 2'000);

  EXPECT_EQ(m_Service3.TotalOrders(), 5);

  EXPECT_FALSE(m_Service3.ExistsOrderId("OrdId2"));
  EXPECT_FALSE(m_Service3.ExistsOrderId("OrdId7"));
  EXPECT_FALSE(m_Service3.ExistsOrderId("OrdId8"));
}

TEST_F(OrderServiceTests, GetMatchingSizeForSecurity)
{
  EXPECT_EQ(m_Service1.TotalOrders(), 13);
  EXPECT_EQ(m_Service2.TotalOrders(), 11);
  EXPECT_EQ(m_Service3.TotalOrders(), 8);

  EXPECT_EQ(m_Service1.GetMatchingSizeForSecurity("SecId1"), 300);
  EXPECT_EQ(m_Service1.GetMatchingSizeForSecurity("SecId2"), 1'000);
  EXPECT_EQ(m_Service1.GetMatchingSizeForSecurity("SecId3"), 600);

  EXPECT_EQ(m_Service2.GetMatchingSizeForSecurity("SecId1"), 900);
  EXPECT_EQ(m_Service2.GetMatchingSizeForSecurity("SecId2"), 600);
  EXPECT_EQ(m_Service2.GetMatchingSizeForSecurity("SecId3"), 0);

  EXPECT_EQ(m_Service3.GetMatchingSizeForSecurity("SecId1"), 0);
  EXPECT_EQ(m_Service3.GetMatchingSizeForSecurity("SecId2"), 2'700);
  EXPECT_EQ(m_Service3.GetMatchingSizeForSecurity("SecId3"), 0);
}
