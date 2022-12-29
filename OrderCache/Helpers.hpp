#ifndef B1032847_0711_4F49_8DCC_FCDF6479F7E1
#define B1032847_0711_4F49_8DCC_FCDF6479F7E1

#include <string_view>
#include <algorithm>

namespace TechnicalTest
{
  bool StringCompareIgnoreCase(const std::string_view str1, const std::string_view str2) noexcept
  {
    return (
        (str1.size() == str2.size()) //
        && std::equal(
               str1.cbegin(),
               str1.cend(),
               str2.cbegin(), //
               [](const char c1, const char c2) { return ::toupper(c1) == ::toupper(c2); }
           )
    );
  }
} // namespace TechnicalTest

#endif /* B1032847_0711_4F49_8DCC_FCDF6479F7E1 */
