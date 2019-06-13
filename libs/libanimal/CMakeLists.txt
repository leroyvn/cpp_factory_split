cmake_minimum_required(VERSION 3.14)

project(libanimal)

set(CMAKE_CXX_STANDARD 14)

file(GLOB sources src/*.cpp)

add_library(libanimal STATIC
    ${sources}
)

target_include_directories(libanimal PUBLIC include)

target_link_libraries(libanimal libfactory)
