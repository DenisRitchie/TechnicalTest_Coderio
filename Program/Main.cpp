#include <iostream>
#include <iomanip>
#include <OrderRepository.hpp>

using namespace TechnicalTest;

int32_t main()
{
  Order order{ "12345", "67890" };

  std::cout << "Order 1" << std::endl                                    //
            << "Order Id: " << std::quoted(order.OrderId()) << std::endl //
            << "Security Id: " << std::quoted(order.SecurityId()) << std::endl
            << std::string(30, '-') << std::endl;

  Order order2 = std::move(order);

  std::cout << "Order 1" << std::endl                                    //
            << "Order Id: " << std::quoted(order.OrderId()) << std::endl //
            << "Security Id: " << std::quoted(order.SecurityId()) << std::endl
            << std::string(30, '-') << std::endl;

  std::cout << "Order 2" << std::endl                                     //
            << "Order Id: " << std::quoted(order2.OrderId()) << std::endl //
            << "Security Id: " << std::quoted(order2.SecurityId()) << std::endl
            << std::string(30, '-') << std::endl;

  std::cout << "\n\n\n";
  return EXIT_SUCCESS;
}