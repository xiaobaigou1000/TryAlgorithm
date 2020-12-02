cmake_minimum_required(VERSION 3.0.0)
project(TryAlgorithm VERSION 0.1.0)

include(CTest)
enable_testing()
add_subdirectory(test)

add_subdirectory(my_binary_tree)
add_subdirectory(my_binary_search_tree)
add_subdirectory(my_sort_algorithm)

add_subdirectory(space_complexity_lab)

find_package(spdlog REQUIRED)

add_executable(TryAlgorithm TryAlgorithm.cpp)
target_link_libraries(TryAlgorithm PRIVATE MySort spdlog::spdlog)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
