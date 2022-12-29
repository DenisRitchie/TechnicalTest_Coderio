#include "Order.hpp"

namespace TechnicalTest
{
  Order::Order(const std::string& order_id, const std::string& security_id, const std::string& side, const uint32_t qty, const std::string& user, const std::string& company)
    : m_OrderId{ order_id }
    , m_SecurityId{ security_id }
    , m_Side{ side }
    , m_Qty{ qty }
    , m_User{ user }
    , m_Company{ company }
  {
  }

  [[nodiscard]] std::string_view Order::OrderId() const noexcept
  {
    return m_OrderId;
  }

  [[nodiscard]] std::string_view Order::SecurityId() const noexcept
  {
    return m_SecurityId;
  }

  [[nodiscard]] std::string_view Order::Side() const noexcept
  {
    return m_Side;
  }

  [[nodiscard]] std::string_view Order::User() const noexcept
  {
    return m_User;
  }

  [[nodiscard]] std::string_view Order::Company() const noexcept
  {
    return m_Company;
  }

  [[nodiscard]] uint32_t Order::Qty() const noexcept
  {
    return m_Qty;
  }

  Order& Order::OrderId(const std::string_view order_id) noexcept
  {
    m_OrderId = order_id;
    return *this;
  }

  Order& Order::SecurityId(const std::string_view security_id) noexcept
  {
    m_SecurityId = security_id;
    return *this;
  }

  Order& Order::Side(const std::string_view side) noexcept
  {
    m_Side = side;
    return *this;
  }

  Order& Order::User(const std::string_view user) noexcept
  {
    m_User = user;
    return *this;
  }

  Order& Order::Company(const std::string_view company) noexcept
  {
    m_Company = company;
    return *this;
  }

  Order& Order::Qty(const uint32_t qty) noexcept
  {
    m_Qty = qty;
    return *this;
  }
} // namespace TechnicalTest