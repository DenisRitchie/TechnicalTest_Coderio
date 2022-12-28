cmake_minimum_required(VERSION 3.12)

project(OrderCache
    LANGUAGES C CXX
    VERSION 1.0.0.0
    DESCRIPTION ""
    HOMEPAGE_URL ""
)

add_library(OrderCache STATIC)
add_library(TechnicalTest::Library::OrderCache ALIAS OrderCache)

target_sources(OrderCache
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/IOrderCache.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/OrderCache.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/OrderCache.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Order.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Order.cpp
)

target_compile_features(OrderCache PUBLIC c_std_11 cxx_std_17)

target_include_directories(OrderCache PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})