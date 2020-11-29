#include "gtest/gtest.h"
#include "pool_allocator.hpp"

class PoolAllocatorTest : public ::testing::Test {
 protected:
  void SetUp() override {
    allocated_memory_ = new unsigned char[memory_size_bytes_];
    pool_allocator_ =
        new allocators::PoolAllocator(allocated_memory_, memory_size_bytes_, block_size_bytes);
  }

  allocators::PoolAllocator* pool_allocator_;
  uint64_t memory_size_bytes_ = 100;
  uint64_t block_size_bytes = 10;
  unsigned char* allocated_memory_;
};

TEST_F(PoolAllocatorTest, AllocationWorks) {
}

TEST_F(PoolAllocatorTest, DeallocationWorks) {
}
