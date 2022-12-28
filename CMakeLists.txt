cmake_minimum_required(VERSION 3.12)

project(TechnicalTest C CXX)

if (MSVC)
  add_compile_options(/WX /W4 /fpermissive)
else()
  add_compile_options(-Wall -Wextra -Werror -pedantic -fpermissive -fstrict-enums)
endif()

add_subdirectory(OrderCache)
add_subdirectory(Program)
