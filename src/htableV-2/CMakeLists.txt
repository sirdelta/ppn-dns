cmake_minimum_required(VERSION 3.21)
project(htable C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(htable
        table.c
        table.h)
