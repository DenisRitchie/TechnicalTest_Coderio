#ifndef D3F54648_C769_4A3C_BDB1_9BA42ECAFA72
#define D3F54648_C769_4A3C_BDB1_9BA42ECAFA72

#include "OrderRepository.hpp"
#include "OrderValidation.hpp"

namespace TechnicalTest
{
  class OrderService
  {
    public:
      // clang-format off

      // add order to the cache
      void AddOrder(const Order& order);

      // remove order with this unique order id from the cache
      void CancelOrder(const std::string_view& order_id);

      // remove all orders in the cache for this user
      void CancelOrdersForUser(const std::string_view user);

      // remove all orders in the cache for this security with qty >= minQty
      void CancelOrdersForSecurityIdWithMinimumQty(const std::string_view security_id, const uint32_t min_qty);

      // return the total qty that can match for the security id
      uint32_t GetMatchingSizeForSecurity(const std::string_view security_id) const noexcept;

      // return all orders in cache in a vector
      const std::vector<Order>& GetAllOrders() const noexcept;

      // clang-format on

    private:
      OrderRepository       m_OrderRepository;
      CreateOrderValidation m_CreateOrderValidation;
  };
} // namespace TechnicalTest

#endif /* D3F54648_C769_4A3C_BDB1_9BA42ECAFA72 */
