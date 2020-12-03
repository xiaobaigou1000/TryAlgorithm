cmake_minimum_required(VERSION 3.12)
project(Examples)

add_executable(NQueenExample n_queen_ex.cpp)
target_link_libraries(NQueenExample PRIVATE NQueen)