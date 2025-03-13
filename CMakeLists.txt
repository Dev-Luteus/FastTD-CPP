cmake_minimum_required(VERSION 3.30)
project(FastTD)

set(CMAKE_CXX_STANDARD 20)

# Add the include directory for headers
include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/lib)

add_executable(FastTD main.cpp
        game.cpp
        game.h
        cell.cpp
        cell.h)

# Link Raylib library (and required Windows libraries)
target_link_libraries(FastTD raylib winmm)