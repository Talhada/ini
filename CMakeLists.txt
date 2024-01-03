cmake_minimum_required(VERSION 3.0)

project(ini VERSION 0.1 LANGUAGES CXX)

option(BUILD_TESTS ON "Build project tests")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add main source directory to build the library
add_subdirectory(src)
 
# Add tests
if(BUILD_TESTS)

	enable_testing()
	find_package(GTest CONFIG REQUIRED)

	add_subdirectory(tests)
	
endif()
