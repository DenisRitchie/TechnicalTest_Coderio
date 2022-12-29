cmake_minimum_required(VERSION 3.12)

project(TechnicalTestProgram C CXX)

add_executable(TechnicalTestProgram Main.cpp)

target_compile_features(TechnicalTestProgram PUBLIC c_std_11 cxx_std_17)

target_include_directories(TechnicalTestProgram PUBLIC ${CMAKE_SOURCE_DIR}/OrderCache)
target_link_libraries(TechnicalTestProgram PUBLIC TechnicalTest::Library::OrderCache)

set_target_properties(TechnicalTestProgram
  PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/output/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/output/bin"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/output/bin"
)
