#include "gtest/gtest.h"
#include "pool_allocator.hpp"

class PoolAllocatorTest : public ::testing::Test {
 protected:
  void SetUpAllocator() {
    allocated_memory_ = new unsigned char[memory_size_bytes_];
    pool_allocator_ =
        new allocators::PoolAllocator(allocated_memory_, memory_size_bytes_, block_size_bytes_);
  }

  allocators::PoolAllocator* pool_allocator_;
  uint64_t memory_size_bytes_ = 80;
  uint64_t block_size_bytes_ = 8;
  unsigned char* allocated_memory_;
};

TEST_F(PoolAllocatorTest, MemoryArenaSizeHasToBeMultipleOfBlockSize) {
  memory_size_bytes_ = 80;
  block_size_bytes_ = 9;
  ASSERT_THROW(SetUpAllocator(), std::logic_error);
}

TEST_F(PoolAllocatorTest, ZeroBytesArenaException) {
  memory_size_bytes_ = 0;
  ASSERT_THROW(SetUpAllocator(), std::logic_error);
}

TEST_F(PoolAllocatorTest, BlockSizeLessThanSizeOfMemoryBlockStructException) {
  block_size_bytes_ = 7;
  ASSERT_THROW(SetUpAllocator(), std::logic_error);
}

TEST_F(PoolAllocatorTest, MemoryArenaPointerNullptrException) {
  allocated_memory_ = nullptr;
  ASSERT_THROW(
      new allocators::PoolAllocator(allocated_memory_, memory_size_bytes_, block_size_bytes_),
      std::logic_error);
}

TEST_F(PoolAllocatorTest, AllocationWorks) {
  SetUpAllocator();
  char* memory_request = nullptr;
  memory_request = static_cast<char*>(pool_allocator_->Allocate());
  ASSERT_NE(memory_request, nullptr);
}

TEST_F(PoolAllocatorTest, DeallocationWorks) {
  SetUpAllocator();
  char* memory_request_1 = nullptr;
  memory_request_1 = static_cast<char*>(pool_allocator_->Allocate());
  ASSERT_NE(memory_request_1, nullptr);
  pool_allocator_->Free(memory_request_1);

  char* memory_request_2 = static_cast<char*>(pool_allocator_->Allocate());
  ASSERT_EQ(memory_request_1, memory_request_2);
}

TEST_F(PoolAllocatorTest, MultipleAllocationsWorks) {
  SetUpAllocator();
  unsigned char* memory_request_1 = static_cast<unsigned char*>(pool_allocator_->Allocate());
  unsigned char* memory_request_2 = static_cast<unsigned char*>(pool_allocator_->Allocate());
  ASSERT_NE(memory_request_2, memory_request_1);
  ASSERT_GE(abs(memory_request_2 - memory_request_1), block_size_bytes_);
}

TEST_F(PoolAllocatorTest, CantAllocateMoreThanNumberOfBlocks) {
  SetUpAllocator();
  for (std::size_t i = 0; i < memory_size_bytes_ / block_size_bytes_; ++i) {
    ASSERT_NE(pool_allocator_->Allocate(), nullptr)
        << "allocation number: " << i << " MemorySize: " << memory_size_bytes_
        << " block_size: " << block_size_bytes_;
  }

  ASSERT_EQ(pool_allocator_->Allocate(), nullptr);
}
