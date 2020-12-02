cmake_minimum_required(VERSION 3.12)
project(SpaceComplexityLab)

find_package(spdlog REQUIRED)

add_executable(SpaceComplexityLab main.cpp)
target_link_libraries(SpaceComplexityLab PRIVATE MySort spdlog::spdlog)
target_include_directories(SpaceComplexityLab PRIVATE include)
