cmake_minimum_required(VERSION 3.15)
project(jzzrenderer)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)
include_directories(.)

add_executable(jzzrenderer
        Vector.h
        my_GL.h
        my_GL.cpp
        main.cpp)
target_link_libraries(jzzrenderer ${OpenCV_LIBRARIES})