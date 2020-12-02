cmake_minimum_required(VERSION 3.12)
project(MySort)

add_library(MySort INTERFACE)
target_include_directories(MySort INTERFACE include)
target_link_libraries(MySort INTERFACE MyBST)
