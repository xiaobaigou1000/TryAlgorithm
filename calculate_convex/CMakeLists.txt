cmake_minimum_required(VERSION 3.12)
project(CalculateConvex)

find_package(glm REQUIRED)

add_library(CalculateConvex INTERFACE)
target_include_directories(CalculateConvex INTERFACE include)
target_link_libraries(CalculateConvex INTERFACE glm)