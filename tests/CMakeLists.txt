project(Allocators)

add_executable(Google_Test_Run stack_allocator_tests.cpp pool_allocator_tests.cpp)
target_link_libraries(Google_Test_Run gtest gtest_main)
target_include_directories(Google_Test_Run PRIVATE "${gtest_SOURCE_DIR}/include" "${gtest_SOURCE_DIR}" "${Allocators_SOURCE_DIR}/include")
target_link_libraries(Google_Test_Run Allocators)