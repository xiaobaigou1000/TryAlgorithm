cmake_minimum_required(VERSION 3.12)
project(BigDecimalMultiplication)

find_package(Boost 1.74 REQUIRED)

add_library(BigDecimalMultiplication INTERFACE)
target_include_directories(BigDecimalMultiplication INTERFACE include)
target_link_libraries(BigDecimalMultiplication INTERFACE Boost::boost)
