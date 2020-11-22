cmake_minimum_required(VERSION 3.10)

project(Allocators)

add_subdirectory(libs)
add_subdirectory(tests)


add_library(Allocators stack_allocator.hpp stack_allocator.cpp)
