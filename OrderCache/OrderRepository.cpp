#include "OrderRepository.hpp"
#include "Helpers.hpp"

#include <algorithm>
#include <numeric>
#include <iterator>
#include <thread>
#include <tuple>
#include <set>

namespace TechnicalTest
{
  // add order to the cache
  void OrderRepository::AddOrder(Order&& order)
  {
    m_Orders.emplace_back(std::move(order));
  }

  // add order to the cache
  void OrderRepository::AddOrder(const Order& order)
  {
    m_Orders.emplace_back(order);
  }

  // verifies that the order by order id exists
  bool OrderRepository::ExistsOrderId(const std::string_view order_id) const noexcept
  {
    auto result = std::find_if(
        m_Orders.cbegin(),
        m_Orders.cend(),        //
        [&](const Order& order) //
        {                       //
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
        m_Orders.end(),         //
        [&](const Order& order) //
        {                       //
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
            m_Orders.end(),         //
            [&](const Order& order) //
            {                       //
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
            m_Orders.end(),         //
            [&](const Order& order) //
            {                       //
              return order.SecurityId() == security_id && order.Qty() >= min_qty;
            }
        ),
        m_Orders.end()
    );
  }

  /*
    - return the total qty that can match for the security id
    - Order matching occurs for orders with the same security id, different side (buy or sell),
      and different company (company of person who requested the order)
    - Order matching rules for GetMatchingSizeForSecurity()
          - Your implementation of GetMatchingSizeForSecurity() should give the total qty that can match for a security id
          - Can only match orders with the same security id
          - Can only match a Buy order with a Sell order
          - Buy order can match against multiple Sell orders (and vice versa)
              - eg a security id "ABCD" has
                  Buy  order with qty 10000
                  Sell order with qty  2000
                  Sell order with qty  1000
              - security id "ABCD" has a total match of 3000. The Buy order's qty is big enough
                to match against both Sell orders and still has 7000 remaining
          - Any order quantity already allocated to a match cannot be reused as a match
            against a differnt order (eg the qty 3000 matched above for security id "ABCD" example)
          - Some orders may not match entirely or at all
          - Users in the same company cannot match against each other
  */
  uint32_t OrderRepository::GetMatchingSizeForSecurity(const std::string_view security_id) const
  {
    uint32_t                                            total_qty = 0;
    std::vector<std::tuple<std::string_view, uint32_t>> buys;
    std::vector<std::tuple<std::string_view, uint32_t>> sells;

    for ( int32_t index = 0; index < m_Orders.size(); ++index )
    {
      if ( m_Orders[index].SecurityId() == security_id )
      {
        if ( StringEquals(m_Orders[index].Side(), "Buy") )
        {
          buys.emplace_back(m_Orders[index].Company(), m_Orders[index].Qty());
        }
        else if ( StringEquals(m_Orders[index].Side(), "Sell") )
        {
          sells.emplace_back(m_Orders[index].Company(), m_Orders[index].Qty());
        }
      }
    }

    for ( auto& [sell_company, sell_qty] : sells )
    {
      for ( auto& [buy_company, buy_qty] : buys )
      {
        if ( sell_company != buy_company )
        {
          uint32_t transaction_qty = 0;

          if ( sell_qty >= buy_qty )
          {
            transaction_qty = buy_qty;
            sell_qty -= transaction_qty;
            buy_qty -= transaction_qty;
          }
          else
          {
            transaction_qty = sell_qty;
            buy_qty -= transaction_qty;
            sell_qty -= transaction_qty;
          }

          total_qty += transaction_qty;

          if ( sell_qty == 0 )
          {
            break;
          }
        }
      }
    }

    return total_qty;
  }

  // return all orders in cache in a vector
  const std::vector<Order>& OrderRepository::GetAllOrders() const
  {
    return m_Orders;
  }

  // total amount of orders
  size_t OrderRepository::TotalOrders() const noexcept
  {
    return m_Orders.size();
  }

  // search for an order by id
  std::optional<Order> OrderRepository::FindOrderById(const std::string_view order_id) const noexcept
  {
    auto result = std::find_if(
        m_Orders.cbegin(),
        m_Orders.cend(),        //
        [&](const Order& order) //
        {                       //
          return order.OrderId() == order_id;
        }
    );

    if ( result != m_Orders.cend() )
    {
      return *result;
    }

    return std::nullopt;
  }
} // namespace TechnicalTest
