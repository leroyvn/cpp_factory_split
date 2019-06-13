# http://mariobadr.com/creating-a-header-only-library-with-cmake.html
cmake_minimum_required(VERSION 3.14)

project(libfactory)

set(CMAKE_CXX_STANDARD 14)

add_library(libfactory INTERFACE)
target_include_directories(libfactory INTERFACE include)
target_sources(libfactory INTERFACE include/factory/Factory.h)
