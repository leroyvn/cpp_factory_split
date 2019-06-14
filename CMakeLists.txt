# https://code.egym.de/how-to-use-modern-cmake-for-an-app-lib-project-3c2ee6018cde

cmake_minimum_required(VERSION 3.14)

project(factory_split)

set(CMAKE_CXX_STANDARD 14)

add_executable(app
    main.cpp)
