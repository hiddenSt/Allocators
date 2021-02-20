
add_executable(Run_Tests stack_allocator_tests.cpp pool_allocator_tests.cpp)
target_link_libraries(Run_Tests gtest gtest_main)
target_include_directories(Run_Tests PRIVATE "${gtest_SOURCE_DIR}/include" "${gtest_SOURCE_DIR}" "${Allocators_SOURCE_DIR}/include")
target_link_libraries(Run_Tests Allocators)
