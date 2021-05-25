cmake_minimum_required(VERSION 3.12)
project(SingleFileAlgorithms)

find_package(spdlog)

set(fileList "")
file(GLOB fileList *.cpp)

foreach(file ${fileList})
	set(fileName "")
	get_filename_component(fileName ${file} NAME_WLE)
	add_executable(${fileName} ${file})
	target_link_libraries(${fileName} PRIVATE spdlog::spdlog)
endforeach()
