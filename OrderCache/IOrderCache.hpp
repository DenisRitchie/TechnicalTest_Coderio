#ifndef D6199F1F_B755_4213_8E10_0ED2482367CD
#define D6199F1F_B755_4213_8E10_0ED2482367CD

#include <vector>
#include <optional>

#include "Order.hpp"

namespace TechnicalTest
{
  // Provide an implementation for the OrderCacheInterface interface class.
  // Your implementation class should hold all relevant data structures you think
  // are needed.
  struct IOrderCache
  {
      // implememnt the 6 methods below, do not alter signatures
      // clang-format off

      // add order to the cache
      virtual void AddOrder(Order&& order) = 0;

      // add order to the cache
      virtual void AddOrder(const Order& order) = 0;

      // verifies that the order by order id exists
      virtual bool ExistsOrderId(const std::string_view order_id) const noexcept = 0;

      // remove order with this unique order id from the cache
      virtual void CancelOrder(const std::string_view& order_id) = 0;

      // remove all orders in the cache for this user
      virtual void CancelOrdersForUser(const std::string_view user) = 0;

      // remove all orders in the cache for this security with qty >= minQty
      virtual void CancelOrdersForSecurityIdWithMinimumQty(const std::string_view security_id, const uint32_t min_qty) = 0;

      // return the total qty that can match for the security id
      virtual uint32_t GetMatchingSizeForSecurity(const std::string_view security_id) = 0;

      // return all orders in cache in a vector
      virtual const std::vector<Order>& GetAllOrders() const = 0;

      // total amount of orders
      virtual size_t TotalOrders() const noexcept = 0;

      // search for an order by id
      virtual std::optional<Order> FindOrderById(const std::string_view order_id) const noexcept = 0;
      // clang-format on
  };
} // namespace TechnicalTest

#endif /* D6199F1F_B755_4213_8E10_0ED2482367CD */
