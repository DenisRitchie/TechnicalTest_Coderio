#ifndef C691240D_0648_4041_BA3B_90CA6A92E818
#define C691240D_0648_4041_BA3B_90CA6A92E818

#include <IOrderCache.hpp>

struct OrderCacheFake : TechnicalTest::IOrderCache
{
    // clang-format off
    virtual void AddOrder(TechnicalTest::Order&& order) override;
    virtual void AddOrder(const TechnicalTest::Order& order) override;
    virtual bool ExistsOrderId(const std::string_view order_id) const noexcept override;
    virtual void CancelOrder(const std::string_view& order_id) override;
    virtual void CancelOrdersForUser(const std::string_view user) override;
    virtual void CancelOrdersForSecurityIdWithMinimumQty(const std::string_view security_id, const uint32_t min_qty) override;
    virtual uint32_t GetMatchingSizeForSecurity(const std::string_view security_id) const override;
    virtual const std::vector<TechnicalTest::Order>& GetAllOrders() const override;
    virtual size_t TotalOrders() const noexcept override;
    virtual std::optional<TechnicalTest::Order> FindOrderById(const std::string_view order_id) const noexcept override;
    // clang-format on
};

#endif /* C691240D_0648_4041_BA3B_90CA6A92E818 */
