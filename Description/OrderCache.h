#pragma once

#include <string>
#include <vector>

class Order
{
  public:
    // do not alter signature of this constructor
    Order(const std::string& ordid, const std::string& secid, const std::string& side, const unsigned int qty, const std::string& user, const std::string& company)
      : m_OrderId(ordid)
      , m_SecurityId(secid)
      , m_Side(side)
      , m_Qty(qty)
      , m_User(user)
      , m_Company(company)
    {
    }

    // do not alter these accessor methods
    std::string OrderId() const
    {
      return m_OrderId;
    }

    std::string SecurityId() const
    {
      return m_SecurityId;
    }

    std::string Side() const
    {
      return m_Side;
    }

    std::string User() const
    {
      return m_User;
    }

    std::string Company() const
    {
      return m_Company;
    }

    unsigned int Qty() const
    {
      return m_Qty;
    }

  private:
    // use the below to hold the order data
    // do not remove the these member variables
    std::string  m_OrderId;    // unique order id
    std::string  m_SecurityId; // security identifier
    std::string  m_Side;       // side of the order, eg Buy or Sell
    unsigned int m_Qty;        // qty for this order
    std::string  m_User;       // user name who owns this order
    std::string  m_Company;    // company for user
};

// Provide an implementation for the OrderCacheInterface interface class.
// Your implementation class should hold all relevant data structures you think
// are needed.
class OrderCacheInterface
{

  public:
    // implememnt the 6 methods below, do not alter signatures

    // add order to the cache
    virtual void               AddOrder(Order order)                                                                  = 0;

    // remove order with this unique order id from the cache
    virtual void               CancelOrder(const std::string& orderId)                                                = 0;

    // remove all orders in the cache for this user
    virtual void               CancelOrdersForUser(const std::string& user)                                           = 0;

    // remove all orders in the cache for this security with qty >= minQty
    virtual void               CancelOrdersForSecIdWithMinimumQty(const std::string& securityId, unsigned int minQty) = 0;

    // return the total qty that can match for the security id
    virtual unsigned int       GetMatchingSizeForSecurity(const std::string& securityId)                              = 0;

    // return all orders in cache in a vector
    virtual std::vector<Order> GetAllOrders() const                                                                   = 0;
};
