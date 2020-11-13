cmake_minimum_required(VERSION 3.10)

project(Allocators)

add_library(Allocators stack_allocator.hpp stack_allocator.cpp)