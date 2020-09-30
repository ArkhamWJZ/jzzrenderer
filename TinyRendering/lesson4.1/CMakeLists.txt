cmake_minimum_required(VERSION 3.15)
project(lesson4_1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lesson4_1
        geometry.cpp
        geometry.h
        main.cpp
        model.cpp
        model.h
        tgaimage.cpp
        tgaimage.h)
