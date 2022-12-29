#ifndef F34FB7C7_957E_43F9_BEF6_32C346EB4C3E
#define F34FB7C7_957E_43F9_BEF6_32C346EB4C3E

#pragma once

#include <string>
#include <string_view>

namespace TechnicalTest
{
  class Order
  {
    public:
      Order() = default;
      Order(const std::string& order_id, const std::string& security_id, const std::string& side, const uint32_t qty, const std::string& user, const std::string& company);

      // clang-format off
      Order& OrderId(const std::string_view order_id) noexcept;
      Order& SecurityId(const std::string_view security_id) noexcept;
      Order& Side(const std::string_view side) noexcept;
      Order& User(const std::string_view user) noexcept;
      Order& Company(const std::string_view company) noexcept;
      Order& Qty(const uint32_t qty) noexcept;
      // clang-format on

      [[nodiscard]] std::string_view OrderId() const noexcept;
      [[nodiscard]] std::string_view SecurityId() const noexcept;
      [[nodiscard]] std::string_view Side() const noexcept;
      [[nodiscard]] std::string_view User() const noexcept;
      [[nodiscard]] std::string_view Company() const noexcept;
      [[nodiscard]] uint32_t         Qty() const noexcept;

    private:
      std::string m_OrderId;    // unique order id
      std::string m_SecurityId; // security identifier
      std::string m_Side;       // side of the order, eg Buy or Sell
      uint32_t    m_Qty;        // qty for this order
      std::string m_User;       // user name who owns this order
      std::string m_Company;    // company for user
  };
} // namespace TechnicalTest

#endif /* F34FB7C7_957E_43F9_BEF6_32C346EB4C3E */
