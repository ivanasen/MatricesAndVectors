cmake_minimum_required(VERSION 3.13)
project(MatricesAndVectors)

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/lib/googletest/googletest/include
        ${PROJECT_SOURCE_DIR}/lib/googletest/googletest)
include_directories(${PROJECT_SOURCE_DIR}/include/)

add_library(MatricesAndVectors INTERFACE)

add_executable(runTests test/matrix_test.cpp test/vector_test.cpp)

target_link_libraries(runTests gtest gtest_main pthread)
target_link_libraries(runTests MatricesAndVectors)

target_include_directories(MatricesAndVectors INTERFACE ${PROJECT_SOURCE_DIR}/include/)