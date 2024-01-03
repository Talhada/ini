cmake_minimum_required(VERSION 3.0)

project(ini VERSION 0.1 LANGUAGES CXX)

option(BUILD_TESTS ON "Build project tests")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)
 
if(BUILD_TESTS)
	add_subdirectory(tests)
endif()
