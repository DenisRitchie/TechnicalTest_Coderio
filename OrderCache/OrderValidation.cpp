#include "OrderValidation.hpp"
#include "Helpers.hpp"

#include <algorithm>

namespace TechnicalTest
{
  CreateOrderValidation::CreateOrderValidation(const IOrderCache& order_repository) noexcept
    : m_OrderRepository{ order_repository }
    , m_ErrorMessages{}
  {
  }

  bool CreateOrderValidation::IsValid(const Order& order) noexcept
  {
    m_ErrorMessages.clear();
    return [&](const auto... results) { //
      return (results && ...);
    }(ValidateOrderId(order), ValidateSecurityId(order), ValidateSide(order), ValidateUser(order), ValidateCompany(order), ValidateQty(order));
  }

  CreateOrderValidation::error_message_t& CreateOrderValidation::Errors() noexcept
  {
    return m_ErrorMessages;
  }

  bool CreateOrderValidation::ValidateOrderId(const Order& order) noexcept
  {
    m_ErrorMessages["OrderId"].clear();

    if ( order.OrderId().empty() )
    {
      m_ErrorMessages["OrderId"].emplace_back("The order id is required.");
    }

    if ( m_OrderRepository.ExistsOrderId(order.OrderId()) )
    {
      m_ErrorMessages["OrderId"].emplace_back("The order id already exists.");
    }

    return m_ErrorMessages["OrderId"].empty();
  }

  bool CreateOrderValidation::ValidateSecurityId(const Order& order) noexcept
  {
    m_ErrorMessages["SecurityId"].clear();

    if ( order.SecurityId().empty() )
    {
      m_ErrorMessages["SecurityId"].emplace_back("The security id is required.");
    }

    return m_ErrorMessages["SecurityId"].empty();
  }

  bool CreateOrderValidation::ValidateSide(const Order& order) noexcept
  {
    m_ErrorMessages["Side"].clear();

    if ( order.Side().empty() )
    {
      m_ErrorMessages["Side"].emplace_back("The side is required.");
    }

    if ( !StringEquals(order.Side(), "Buy") && //
         !StringEquals(order.Side(), "Sell") )
    {
      m_ErrorMessages["Side"].emplace_back("The side must be \"Buy\" or \"Sell\".");
    }

    return m_ErrorMessages["Side"].empty();
  }

  bool CreateOrderValidation::ValidateUser(const Order& order) noexcept
  {
    m_ErrorMessages["User"].clear();

    if ( order.User().empty() )
    {
      m_ErrorMessages["User"].emplace_back("The user is required.");
    }

    return m_ErrorMessages["User"].empty();
  }

  bool CreateOrderValidation::ValidateCompany(const Order& order) noexcept
  {
    m_ErrorMessages["Company"].clear();

    if ( order.Company().empty() )
    {
      m_ErrorMessages["Company"].emplace_back("The company is required.");
    }

    return m_ErrorMessages["Company"].empty();
  }

  bool CreateOrderValidation::ValidateQty([[maybe_unused]] const Order& order) noexcept
  {
    return true;
  }
} // namespace TechnicalTest
