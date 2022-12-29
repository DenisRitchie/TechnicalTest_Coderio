cmake_minimum_required(VERSION 3.12)

project(TechnicalTest
  LANGUAGES C CXX
  VERSION 1.0.0.0
  DESCRIPTION "Technical Test Coderio"
  HOMEPAGE_URL "https://github.com/DenisRitchie/TechnicalTest_Coderio"
)

if (MSVC)
  add_compile_options(/WX /W4 /permissive /Zc:__cplusplus)
else()
  add_compile_options(-Wall -Wextra -Werror -pedantic -fpermissive -fstrict-enums)
endif()

add_subdirectory(OrderCache)
add_subdirectory(Program)
add_subdirectory(Tests)
