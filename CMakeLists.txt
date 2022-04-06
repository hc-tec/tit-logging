cmake_minimum_required(VERSION 3.17)
project(tit-logging)

set(CMAKE_CXX_STANDARD 17)

set(CXX_FLAGS
        -std=c++17
        -g
        -Wall
        -O0
        -Wno-unused-variable)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)


include_directories(src)
include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory(src/base)
add_subdirectory(src/log)

# just for test
aux_source_directory(. DIR_SRCS)

add_executable(tit-logging ${DIR_SRCS})


target_link_libraries(tit-logging
        tit_log # link tit_logging
        tit_base
        )
