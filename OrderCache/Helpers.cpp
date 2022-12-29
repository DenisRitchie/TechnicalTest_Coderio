#include "Helpers.hpp"

#include <algorithm>
#include <cctype>

namespace TechnicalTest
{
  bool StringEquals(const std::string_view str1, const std::string_view str2) noexcept
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

  int32_t StringCompareIgnoreCase(const std::string_view str1, const std::string_view str2) noexcept
  {
    const unsigned char* s1 = (const unsigned char*)str1.data();
    const unsigned char* s2 = (const unsigned char*)str2.data();
    unsigned char        c1, c2;

    do
    {
      c1 = (unsigned char)::toupper(*s1++);
      c2 = (unsigned char)::toupper(*s2++);

      if ( c1 == '\0' )
      {
        return c1 - c2;
      }
    }
    while ( c1 == c2 );

    return c1 - c2;
  }
} // namespace TechnicalTest
