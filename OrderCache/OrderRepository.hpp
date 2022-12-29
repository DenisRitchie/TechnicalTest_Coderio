#ifndef C1F0FEA4_CECB_4FF2_A536_3757C30C6D42
#define C1F0FEA4_CECB_4FF2_A536_3757C30C6D42

#include "IOrderCache.hpp"

namespace TechnicalTest
{
  class OrderRepository : public IOrderCache
  {
    public:
      // clang-format off

      // add order to the cache
      virtual void AddOrder(Order&& order) override;

      // add order to the cache
      virtual void AddOrder(const Order& order) override;

      // verifies that the order by order id exists
      virtual bool ExistsOrderId(const std::string_view order_id) const noexcept override;

      // remove order with this unique order id from the cache
      virtual void CancelOrder(const std::string_view& order_id) override;

      // remove all orders in the cache for this user
      virtual void CancelOrdersForUser(const std::string_view user) override;

      // remove all orders in the cache for this security with qty >= minQty
      virtual void CancelOrdersForSecurityIdWithMinimumQty(const std::string_view security_id, const uint32_t min_qty) override;

      // return the total qty that can match for the security id
      virtual uint32_t GetMatchingSizeForSecurity(const std::string_view security_id) override;

      // return all orders in cache in a vector
      virtual const std::vector<Order>& GetAllOrders() const override;

      // total amount of orders
      virtual size_t TotalOrders() const noexcept override;

      // search for an order by id
      virtual std::optional<Order> FindOrderById(const std::string_view order_id) const noexcept override;

      // clang-format on

    private:
      std::vector<Order> m_Orders;
  };
} // namespace TechnicalTest

#endif /* C1F0FEA4_CECB_4FF2_A536_3757C30C6D42 */
