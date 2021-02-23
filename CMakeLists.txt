cmake_minimum_required(VERSION 3.14)
project(allocators VERSION 1.0)

include(cmake/ClangFormat.cmake)
include(cmake/ClangTidy.cmake)

option(ALLOCATORS_DEVELOPER "Allocators development mode" OFF)
option(ALLOCATORS_TESTS "Enable Allocators tests" OFF)

add_subdirectory(third-party)

add_subdirectory(allocators)

if(ALLOCATORS_TESTS OR ALLOCATORS_DEVELOPER)
  add_subdirectory(tests)
endif()