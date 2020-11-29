project(Allocators)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Google_Test_Run stack_allocator_tests.cpp pool_allocator_tests.cpp)
target_link_libraries(Google_Test_Run gtest gtest_main)
target_link_libraries(Google_Test_Run Allocators)