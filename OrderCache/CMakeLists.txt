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
        ${CMAKE_CURRENT_SOURCE_DIR}/OrderRepository.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/OrderRepository.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/OrderService.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/OrderService.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/OrderValidation.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/OrderValidation.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Order.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Order.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Helpers.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Helpers.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/OrderException.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/OrderException.cpp
)

target_compile_features(OrderCache PUBLIC c_std_11 cxx_std_17)

target_include_directories(OrderCache PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
