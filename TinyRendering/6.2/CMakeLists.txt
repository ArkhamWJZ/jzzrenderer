cmake_minimum_required(VERSION 3.15)
project(6_2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(6_2
        geometry.cpp
        geometry.h
        main.cpp
        model.cpp
        model.h
        our_gl.cpp
        our_gl.h
        tgaimage.cpp
        tgaimage.h)
