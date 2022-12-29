#ifndef BA2A5128_A05F_4283_A5B3_D5FBB3BC54F5
#define BA2A5128_A05F_4283_A5B3_D5FBB3BC54F5

#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>

namespace TechnicalTest
{
  class OrderException : public std::invalid_argument
  {
    public:
      using std::invalid_argument::invalid_argument;
      OrderException(const char* error_message, std::unordered_map<std::string, std::vector<std::string>>&& errors) noexcept;
      const std::unordered_map<std::string, std::vector<std::string>>& Errors() const noexcept;

    private:
      std::unordered_map<std::string, std::vector<std::string>> m_Errors;
  };
} // namespace TechnicalTest

#endif /* BA2A5128_A05F_4283_A5B3_D5FBB3BC54F5 */
