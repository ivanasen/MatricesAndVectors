cmake_minimum_required(VERSION 3.13)
project(MatricesAndVectors)

set(CMAKE_CXX_STANDARD 17)

include_directories(../lib/googletest/googletest/include ../lib/googletest/googletest)
include_directories(include/)

add_library(MatricesAndVectors INTERFACE)

add_executable(runTests test/MatrixTest.cpp)

target_link_libraries(runTests gtest gtest_main pthread)
target_link_libraries(runTests MatricesAndVectors)

target_include_directories(MatricesAndVectors INTERFACE include/)