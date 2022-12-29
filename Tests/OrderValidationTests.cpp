#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <OrderRepository.hpp>
#include <OrderValidation.hpp>

#include "OrderCacheFake.hpp"

using ::testing::_;
using ::testing::AnyNumber;

using namespace TechnicalTest;
using namespace std::string_literals;
using namespace std::string_view_literals;

namespace
{
  class OrderRepositoryMock : public OrderCacheFake
  {
    public:
      OrderRepositoryMock(const bool exists_order_id_method_return)
      {
        ON_CALL(*this, ExistsOrderId)
            .WillByDefault(                                                            //
                [this, exists_order_id_method_return](const std::string_view order_id) //
                {                                                                      //
                  return exists_order_id_method_return;
                }
            );
      }

      MOCK_METHOD(bool, ExistsOrderId, (const std::string_view order_id), (const, noexcept, override));
  };
} // namespace

TEST(OrderValidationTests, CreateModelOrderValidation_Success)
{
  OrderRepositoryMock mock_false{ false };

  EXPECT_CALL(mock_false, ExistsOrderId(_)).Times(AnyNumber());
  EXPECT_FALSE(mock_false.ExistsOrderId("OrderId1"));

  // clang-format off
  Order order{ "OrderId1", "SecurityId1", "Buy", 1'000, "User1", "Coderio" };
  CreateOrderValidation validator_noexists_order{ mock_false };
  EXPECT_TRUE(validator_noexists_order.IsValid(order));
  auto&& error_message = validator_noexists_order.Errors();
  // clang-format on

  EXPECT_TRUE(error_message["OrderId"].empty());
  EXPECT_TRUE(error_message["SecurityId"].empty());
  EXPECT_TRUE(error_message["Side"].empty());
  EXPECT_TRUE(error_message["User"].empty());
  EXPECT_TRUE(error_message["Company"].empty());
  EXPECT_TRUE(error_message["Qty"].empty());
}

TEST(OrderValidationTests, CreateModelOrderValidation_SideError)
{
  OrderRepositoryMock mock_false{ false };

  EXPECT_CALL(mock_false, ExistsOrderId(_)).Times(AnyNumber());
  EXPECT_FALSE(mock_false.ExistsOrderId("OrderId1"));

  // clang-format off
  Order order{ "OrderId1", "SecurityId1", "Side", 1'000, "User1", "Coderio" };
  CreateOrderValidation validator_noexists_order{ mock_false };
  EXPECT_FALSE(validator_noexists_order.IsValid(order));
  auto&& error_message = validator_noexists_order.Errors();
  // clang-format on

  EXPECT_TRUE(error_message["OrderId"].empty());
  EXPECT_TRUE(error_message["SecurityId"].empty());
  EXPECT_FALSE(error_message["Side"].empty());
  EXPECT_TRUE(error_message["User"].empty());
  EXPECT_TRUE(error_message["Company"].empty());
  EXPECT_TRUE(error_message["Qty"].empty());

  EXPECT_EQ(error_message["Side"].size(), 1);
  EXPECT_EQ(error_message["Side"][0], "The side must be \"Buy\" or \"Sell\"."s);
}

TEST(OrderValidationTests, CreateModelOrderValidation_ExistsOrderId)
{
  OrderRepositoryMock mock_true{ true };

  EXPECT_CALL(mock_true, ExistsOrderId(_)).Times(AnyNumber());
  EXPECT_TRUE(mock_true.ExistsOrderId("OrderId1"));

  // clang-format off
  Order order;
  CreateOrderValidation validator_exists_order{ mock_true };
  EXPECT_FALSE(validator_exists_order.IsValid(order));
  auto&& error_message = validator_exists_order.Errors();
  // clang-format on

  EXPECT_FALSE(error_message["OrderId"].empty());
  EXPECT_FALSE(error_message["SecurityId"].empty());
  EXPECT_FALSE(error_message["Side"].empty());
  EXPECT_FALSE(error_message["User"].empty());
  EXPECT_FALSE(error_message["Company"].empty());
  EXPECT_TRUE(error_message["Qty"].empty());

  EXPECT_EQ(error_message["OrderId"].size(), 2);
  EXPECT_EQ(error_message["OrderId"][0], "The order id is required."s);
  EXPECT_EQ(error_message["OrderId"][1], "The order id already exists."s);

  EXPECT_EQ(error_message["SecurityId"].size(), 1);
  EXPECT_EQ(error_message["SecurityId"][0], "The security id is required."s);

  EXPECT_EQ(error_message["Side"].size(), 2);
  EXPECT_EQ(error_message["Side"][0], "The side is required."s);
  EXPECT_EQ(error_message["Side"][1], "The side must be \"Buy\" or \"Sell\"."s);

  EXPECT_EQ(error_message["User"].size(), 1);
  EXPECT_EQ(error_message["User"][0], "The user is required."s);

  EXPECT_EQ(error_message["Company"].size(), 1);
  EXPECT_EQ(error_message["Company"][0], "The company is required."s);
}

TEST(OrderValidationTests, CreateModelOrderValidation_NotExistsOrderId)
{
  OrderRepositoryMock mock_false{ false };

  EXPECT_CALL(mock_false, ExistsOrderId(_)).Times(AnyNumber());
  EXPECT_FALSE(mock_false.ExistsOrderId("OrderId1"));

  // clang-format off
  Order order;
  CreateOrderValidation validator_noexists_order{ mock_false };
  EXPECT_FALSE(validator_noexists_order.IsValid(order));
  auto&& error_message = validator_noexists_order.Errors();
  // clang-format on

  EXPECT_FALSE(error_message["OrderId"].empty());
  EXPECT_FALSE(error_message["SecurityId"].empty());
  EXPECT_FALSE(error_message["Side"].empty());
  EXPECT_FALSE(error_message["User"].empty());
  EXPECT_FALSE(error_message["Company"].empty());
  EXPECT_TRUE(error_message["Qty"].empty());

  EXPECT_EQ(error_message["OrderId"].size(), 1);
  EXPECT_EQ(error_message["OrderId"][0], "The order id is required."s);

  EXPECT_EQ(error_message["SecurityId"].size(), 1);
  EXPECT_EQ(error_message["SecurityId"][0], "The security id is required."s);

  EXPECT_EQ(error_message["Side"].size(), 2);
  EXPECT_EQ(error_message["Side"][0], "The side is required."s);
  EXPECT_EQ(error_message["Side"][1], "The side must be \"Buy\" or \"Sell\"."s);

  EXPECT_EQ(error_message["User"].size(), 1);
  EXPECT_EQ(error_message["User"][0], "The user is required."s);

  EXPECT_EQ(error_message["Company"].size(), 1);
  EXPECT_EQ(error_message["Company"][0], "The company is required."s);
}
