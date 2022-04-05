cmake_minimum_required(VERSION 3.17)
project(logging)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g -Wall -O0 -Wno-unused-variable")


aux_source_directory(. DIR_SRCS)


add_executable(logging ${DIR_SRCS})

