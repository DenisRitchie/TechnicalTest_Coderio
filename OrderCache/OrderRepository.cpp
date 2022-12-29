#include "OrderRepository.hpp"
#include <algorithm>

namespace TechnicalTest
{
  // add order to the cache
  void OrderRepository::AddOrder(const Order& order)
  {
    m_Orders.emplace_back(std::move(order));
  }

  // verifies that the order by order id exists
  bool OrderRepository::ExistsOrderId(const std::string_view order_id) const noexcept
  {
    auto result = std::find_if(
        m_Orders.cbegin(),
        m_Orders.cend(),                //
        [&order_id](const Order& order) //
        {                               //
          return order.OrderId() == order_id;
        }
    );

    return result != m_Orders.cend();
  }

  // remove order with this unique order id from the cache
  void OrderRepository::CancelOrder(const std::string_view& order_id)
  {
    auto result = std::find_if(
        m_Orders.begin(),
        m_Orders.end(),                 //
        [&order_id](const Order& order) //
        {                               //
          return order.OrderId() == order_id;
        }
    );

    if ( result != m_Orders.end() )
    {
      m_Orders.erase(result);
    }
  }

  // remove all orders in the cache for this user
  void OrderRepository::CancelOrdersForUser(const std::string_view user)
  {
    m_Orders.erase( //
        std::remove_if(
            m_Orders.begin(),
            m_Orders.end(),             //
            [&user](const Order& order) //
            {                           //
              return order.User() == user;
            }
        ),
        m_Orders.end()
    );
  }

  // remove all orders in the cache for this security with qty >= minQty
  void OrderRepository::CancelOrdersForSecurityIdWithMinimumQty(const std::string_view security_id, const uint32_t min_qty)
  {
    m_Orders.erase( //
        std::remove_if(
            m_Orders.begin(),
            m_Orders.end(),                              //
            [&security_id, &min_qty](const Order& order) //
            {                                            //
              return order.SecurityId() == security_id && order.Qty() >= min_qty;
            }
        ),
        m_Orders.end()
    );
  }

  // return the total qty that can match for the security id
  uint32_t OrderRepository::GetMatchingSizeForSecurity(const std::string_view security_id)
  {
    uint32_t total_qty = 0;

    for ( const Order& order : m_Orders )
    {
      if ( order.SecurityId() == security_id )
      {
        total_qty += order.Qty();
      }
    }

    return total_qty;
  }

  // return all orders in cache in a vector
  const std::vector<Order>& OrderRepository::GetAllOrders() const
  {
    return m_Orders;
  }
} // namespace TechnicalTest
