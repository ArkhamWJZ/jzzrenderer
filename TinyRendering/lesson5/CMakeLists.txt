cmake_minimum_required(VERSION 3.15)
project(lesson5)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lesson5
        geometry.cpp
        geometry.h
        main.cpp
        model.cpp
        model.h
        tgaimage.cpp
        tgaimage.h)
