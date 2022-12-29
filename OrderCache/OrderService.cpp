#include "OrderService.hpp"
#include "OrderException.hpp"

namespace TechnicalTest
{
  // add order to the cache
  void OrderService::AddOrder(const Order& order)
  {
    if ( m_CreateOrderValidation.IsValid(order) )
    {
      m_OrderRepository.AddOrder(order);
    }
    else
    {
      throw OrderException(
          "Order model validation error.", //
          std::move(const_cast<CreateOrderValidation::error_message_t&>(m_CreateOrderValidation.ErrorMessages()))
      );
    }
  }

  // remove order with this unique order id from the cache
  void OrderService::CancelOrder(const std::string_view& order_id)
  {
    if ( order_id.empty() )
    {
      throw OrderException("The order id is required.");
    }

    m_OrderRepository.CancelOrder(order_id);
  }

  // remove all orders in the cache for this user
  void OrderService::CancelOrdersForUser(const std::string_view user)
  {
    if ( user.empty() )
    {
      throw OrderException("The user is required.");
    }

    m_OrderRepository.CancelOrdersForUser(user);
  }

  // remove all orders in the cache for this security with qty >= minQty
  void OrderService::CancelOrdersForSecurityIdWithMinimumQty(const std::string_view security_id, const uint32_t min_qty)
  {
    if ( security_id.empty() )
    {
      throw OrderException("The security id is required.");
    }

    m_OrderRepository.CancelOrdersForSecurityIdWithMinimumQty(security_id, min_qty);
  }

  // return the total qty that can match for the security id
  uint32_t OrderService::GetMatchingSizeForSecurity(const std::string_view security_id) const noexcept
  {
    if ( security_id.empty() )
    {
      throw OrderException("The security id is required.");
    }

    return m_OrderRepository.GetMatchingSizeForSecurity(security_id);
  }

  // return all orders in cache in a vector
  const std::vector<Order>& OrderService::GetAllOrders() const noexcept
  {
    return m_OrderRepository.GetAllOrders();
  }
} // namespace TechnicalTest
