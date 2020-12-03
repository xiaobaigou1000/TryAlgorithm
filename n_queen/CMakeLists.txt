cmake_minimum_required(VERSION 3.12)
project(NQueen)

add_library(NQueen INTERFACE)
target_include_directories(NQueen INTERFACE include)

add_executable(NQueenTest nqueen.cpp)
target_link_libraries(NQueenTest PRIVATE NQueen)
