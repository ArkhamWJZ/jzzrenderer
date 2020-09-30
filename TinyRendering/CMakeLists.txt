cmake_minimum_required(VERSION 3.15)
project(TinyRendering)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

aux_source_directory(. DIR_SRCS)

add_executable(TinyRendering ${DIR_SRCS})

