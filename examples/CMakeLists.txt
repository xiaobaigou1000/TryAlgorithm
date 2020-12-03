cmake_minimum_required(VERSION 3.12)
project(Examples)

add_executable(NQueenExample n_queen_ex.cpp)
target_link_libraries(NQueenExample PRIVATE NQueen ComplexityBenchmarkUtil)

add_executable(Fuck big_int_test.cpp)
target_link_libraries(Fuck PRIVATE BigDecimalMultiplication ComplexityBenchmarkUtil)