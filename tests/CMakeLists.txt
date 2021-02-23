add_executable(Run_Allocators_Tests stack_allocator_tests.cpp pool_allocator_tests.cpp)

target_link_libraries(Run_Allocators_Tests gtest gtest_main)
target_include_directories(Run_Allocators_Tests PRIVATE "${gtest_SOURCE_DIR}/include" "${gtest_SOURCE_DIR}" "${allocators_SOURCE_DIR}")
target_link_libraries(Run_Allocators_Tests allocators)
