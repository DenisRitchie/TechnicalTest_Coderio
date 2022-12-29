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

      CreateOrderValidation(const IOrderCache& order_repository) noexcept;
      error_message_t& Errors() noexcept;

      // clang-format off
      bool IsValid(const Order& order) noexcept;
      bool ValidateOrderId(const Order& order) noexcept;
      bool ValidateSecurityId(const Order& order) noexcept;
      bool ValidateSide(const Order& order) noexcept;
      bool ValidateUser(const Order& order) noexcept;
      bool ValidateCompany(const Order& order) noexcept;
      bool ValidateQty(const Order& order) noexcept;
      // clang-format on

    private:
      error_message_t    m_ErrorMessages;
      const IOrderCache& m_OrderRepository;
  };
}; // namespace TechnicalTest

#endif /* C0E1F25E_1D69_43F3_A3B0_DE311329257A */
