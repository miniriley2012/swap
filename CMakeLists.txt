cmake_minimum_required(VERSION 3.20)
project(swap C)

set(CMAKE_C_STANDARD 11)

add_executable(swap main.c)

install(TARGETS swap)
