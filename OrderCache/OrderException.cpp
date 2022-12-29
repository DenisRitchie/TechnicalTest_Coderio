#include "OrderException.hpp"

namespace TechnicalTest
{
  OrderException::OrderException(const char* error_message, std::unordered_map<std::string, std::vector<std::string>>&& errors) noexcept
    : std::invalid_argument{ error_message }
    , m_Errors{ std::move(errors) }
  {
  }

  const std::unordered_map<std::string, std::vector<std::string>>& OrderException::Errors() const noexcept
  {
    return m_Errors;
  }
} // namespace TechnicalTest
