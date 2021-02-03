cmake_minimum_required(VERSION 3.10)

project(Allocators)

get_filename_component(LIB_PATH "." ABSOLUTE)

file(GLOB_RECURSE LIB_HEADERS ${LIB_PATH}/include/*.hpp)
file(GLOB_RECURSE LIB_CXX_SOURCES ${LIB_PATH}/src/*.cpp)

add_library(Allocators ${LIB_HEADERS} ${LIB_CXX_SOURCES})
target_include_directories(Allocators PUBLIC ${LIB_PATH}/include)

add_subdirectory(libs)
add_subdirectory(tests)
