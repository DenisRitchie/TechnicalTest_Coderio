cmake_minimum_required(VERSION 3.12)

project(TechnicalTestTests
    LANGUAGES C CXX
    VERSION 1.0.0.0
    DESCRIPTION "Test: ${CMAKE_PROJECT_DESCRIPTION}"
    HOMEPAGE_URL "https://github.com/DenisRitchie/TechnicalTest_Coderio"
)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(TEST_PROJECT_NAME TechnicalTestTests)

add_executable(${TEST_PROJECT_NAME}
    MainTests.cpp
    HelpersTests.cpp
    OrderModelTests.cpp
    OrderRepositoryTests.cpp
    OrderServiceTests.cpp
    OrderValidationTests.cpp
    OrderCacheFake.hpp
    OrderCacheFake.cpp
)

target_link_libraries(${TEST_PROJECT_NAME}
    PUBLIC
        GTest::gtest_main
        GTest::gmock_main
        TechnicalTest::Library::OrderCache
)

target_include_directories(${TEST_PROJECT_NAME}
    PUBLIC
        ${CMAKE_SOURCE_DIR}/OrderCache
)

target_compile_features(${TEST_PROJECT_NAME} PUBLIC c_std_11 cxx_std_17)

include(GoogleTest)
gtest_discover_tests(${TEST_PROJECT_NAME} TEST_PREFIX TechnicalTest)

set_target_properties(${TEST_PROJECT_NAME}
    PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/output/bin"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/output/bin"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/output/bin"
)

if (MSVC)
    add_custom_command(
        TARGET ${TEST_PROJECT_NAME} POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/Data/TestData1.txt" "${CMAKE_BINARY_DIR}/output/bin/$<CONFIG>/Data/TestData1.txt"
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/Data/TestData2.txt" "${CMAKE_BINARY_DIR}/output/bin/$<CONFIG>/Data/TestData2.txt"
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/Data/TestData3.txt" "${CMAKE_BINARY_DIR}/output/bin/$<CONFIG>/Data/TestData3.txt"
    )
else()
    add_custom_command(
        TARGET ${TEST_PROJECT_NAME} POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/Data/TestData1.txt" "${CMAKE_BINARY_DIR}/output/bin/Data/TestData1.txt"
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/Data/TestData2.txt" "${CMAKE_BINARY_DIR}/output/bin/Data/TestData2.txt"
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/Data/TestData3.txt" "${CMAKE_BINARY_DIR}/output/bin/Data/TestData3.txt"
    )
endif()