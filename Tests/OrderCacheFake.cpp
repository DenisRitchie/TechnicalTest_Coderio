#include "OrderCacheFake.hpp"

void OrderCacheFake::AddOrder([[maybe_unused]] TechnicalTest::Order&& order)
{
}

void OrderCacheFake::AddOrder([[maybe_unused]] const TechnicalTest::Order& order)
{
}

bool OrderCacheFake::ExistsOrderId([[maybe_unused]] const std::string_view order_id) const noexcept
{
  return false;
}

void OrderCacheFake::CancelOrder([[maybe_unused]] const std::string_view& order_id)
{
}

void OrderCacheFake::CancelOrdersForUser([[maybe_unused]] const std::string_view user)
{
}

void OrderCacheFake::CancelOrdersForSecurityIdWithMinimumQty([[maybe_unused]] const std::string_view security_id, [[maybe_unused]] const uint32_t min_qty)
{
}

uint32_t OrderCacheFake::GetMatchingSizeForSecurity([[maybe_unused]] const std::string_view security_id)
{
  return 0;
}

const std::vector<TechnicalTest::Order>& OrderCacheFake::GetAllOrders() const
{
  static std::vector<TechnicalTest::Order> default_value;
  return default_value;
}

size_t OrderCacheFake::TotalOrders() const noexcept
{
  return 0;
}

std::optional<TechnicalTest::Order> OrderCacheFake::FindOrderById([[maybe_unused]] const std::string_view order_id) const noexcept
{
  return std::nullopt;
}
