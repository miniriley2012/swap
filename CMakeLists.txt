cmake_minimum_required(VERSION 3.20)
project(swap C)

set(CMAKE_C_STANDARD 11)

add_library(libswap src/swap.c)
set_target_properties(libswap PROPERTIES
        OUTPUT_NAME "swap"
        PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/include/swap/swap.h")
target_include_directories(libswap PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_executable(swap main.c)
target_link_libraries(swap libswap)

install(TARGETS libswap swap
        LIBRARY
        PUBLIC_HEADER)
