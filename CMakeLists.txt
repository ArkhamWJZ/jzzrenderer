cmake_minimum_required(VERSION 3.15)
project(jzzrenderer)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(jzzrenderer
        Vector.cpp
        Vector.h)
