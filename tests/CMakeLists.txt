cmake_minimum_required(VERSION 3.0)

include_directories("../src/include")

add_executable(Test main.cpp)
target_link_libraries(Test ini)

#file(COPY "samples/sample_1.ini" DESTINATION "${CMAKE_BINARY_DIR}/tests")
#file(COPY "samples/sample_2.ini" DESTINATION "${CMAKE_BINARY_DIR}/tests") 
#file(COPY "samples/sample_3.ini" DESTINATION "${CMAKE_BINARY_DIR}/tests")


# Install 
install(TARGETS Test DESTINATION bin)
target_link_libraries(Test GTest::gtest GTest::gtest_main)

# Add tests
include(GoogleTest)
gtest_discover_tests(Test)