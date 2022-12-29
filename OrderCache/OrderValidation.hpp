#ifndef C0E1F25E_1D69_43F3_A3B0_DE311329257A
#define C0E1F25E_1D69_43F3_A3B0_DE311329257A

#include "OrderRepository.hpp"
#include <unordered_map>
#include <vector>

namespace TechnicalTest
{
  class CreateOrderValidation
  {
    public:
      using error_message_t = std::unordered_map<std::string, std::vector<std::string>>;

      CreateOrderValidation(const OrderRepository& order_repository) noexcept;
      const error_message_t& ErrorMessages() const noexcept;

      // clang-format off
      bool IsValid(const Order& order) const noexcept;
      bool ValidateOrderId(const Order& order) const noexcept;
      bool ValidateSecurityId(const Order& order) const noexcept;
      bool ValidateSide(const Order& order) const noexcept;
      bool ValidateUser(const Order& order) const noexcept;
      bool ValidateCompany(const Order& order) const noexcept;
      bool ValidateQty(const Order& order) const noexcept;
      // clang-format on

    private:
      mutable error_message_t m_ErrorMessages;
      const OrderRepository&  m_OrderRepository;
  };
}; // namespace TechnicalTest

#endif /* C0E1F25E_1D69_43F3_A3B0_DE311329257A */
