#ifndef B1032847_0711_4F49_8DCC_FCDF6479F7E1
#define B1032847_0711_4F49_8DCC_FCDF6479F7E1

#include <string_view>

namespace TechnicalTest
{
  bool    StringEquals(const std::string_view str1, const std::string_view str2) noexcept;
  int32_t StringCompareIgnoreCase(const std::string_view str1, const std::string_view str2) noexcept;
} // namespace TechnicalTest

#endif /* B1032847_0711_4F49_8DCC_FCDF6479F7E1 */
