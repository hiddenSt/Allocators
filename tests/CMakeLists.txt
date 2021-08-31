add_executable(allocators-lib-tests stack_allocator_tests.cpp pool_allocator_tests.cpp pointer_arithmetic_tests.cpp)

target_link_libraries(allocators-lib-tests PRIVATE gtest gtest_main)
target_include_directories(allocators-lib-testss PRIVATE "${gtest_SOURCE_DIR}/include" "${gtest_SOURCE_DIR}" "${allocators_SOURCE_DIR}")
target_link_libraries(allocators-lib-tests PRIVATE allocators)

