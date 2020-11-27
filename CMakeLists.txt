cmake_minimum_required(VERSION 3.10)

project(Allocators)

include_directories(include)

add_subdirectory(libs)
add_subdirectory(tests)



set(HEADERS include/stack_allocator.hpp)
set(SOURCES src/stack_allocator.cpp)

add_library(Allocators ${HEADERS} ${SOURCES})
