cmake_minimum_required(VERSION 3.0)

include_directories("include")

# Build
add_library(ini "include/ini/document.h" "document.cpp")

# Install 
install(TARGETS ini)
  