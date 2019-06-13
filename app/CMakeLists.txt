cmake_minimum_required(VERSION 3.14)
project(factory_split_app)

set(CMAKE_CXX_STANDARD 14)

add_executable(app src/main.cpp)
target_link_libraries(app PRIVATE libanimal)
