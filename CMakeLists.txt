cmake_minimum_required(VERSION 3.0.0)
project(TryAlgorithm VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)

include(CTest)
enable_testing()
add_subdirectory(test)

add_subdirectory(my_binary_tree)
add_subdirectory(my_binary_search_tree)
add_subdirectory(my_sort_algorithm)
add_subdirectory(big_decimal_multiplication)
add_subdirectory(calculate_convex)
add_subdirectory(sequence_dp)
add_subdirectory(zero_one_backpack)
add_subdirectory(complexity_benchmark_util)
add_subdirectory(n_queen)
add_subdirectory(single_file_algorithms)

add_subdirectory(examples)

add_subdirectory(space_complexity_lab)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
