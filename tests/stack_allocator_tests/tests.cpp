#include "../../stack_allocator.hpp"
#include "gtest/gtest.h"

class StackAllocatorTest : public ::testing::Test {
 protected:
  void SetUp() override {
    allocated_memory_ = new unsigned char[memory_size_bytes_];
    stack_allocator_ = new allocators::StackAllocator(allocated_memory_, memory_size_bytes_);
  }

  const uint64_t memory_size_bytes_ = 100;
  unsigned char* allocated_memory_;
  allocators::StackAllocator* stack_allocator_;
};

TEST_F(StackAllocatorTest, AllocationWorks) {
  char* memory_request = nullptr;
  memory_request = static_cast<char*>(stack_allocator_->Allocate(5));
  ASSERT_NE(memory_request, nullptr);
}

TEST_F(StackAllocatorTest, DeallocationWorks) {
  char* memory_request_1 = nullptr;
  memory_request_1 = static_cast<char*>(stack_allocator_->Allocate(5));
  ASSERT_NE(memory_request_1, nullptr);

  stack_allocator_->Deallocate();

  char* memory_request_2 = nullptr;
  memory_request_2 = static_cast<char*>(stack_allocator_->Allocate(10));
  ASSERT_EQ(memory_request_2, memory_request_1);
}

TEST_F(StackAllocatorTest, MultipleAllocationsWorks) {
  char* memory_request_1 = nullptr;
  memory_request_1 = static_cast<char*>(stack_allocator_->Allocate(5));
  ASSERT_NE(memory_request_1, nullptr);

  char* memory_request_2 = nullptr;
  memory_request_2 = static_cast<char*>(stack_allocator_->Allocate(5));
  ASSERT_NE(memory_request_2, nullptr);

  ASSERT_NE(memory_request_1, memory_request_2);
}

TEST_F(StackAllocatorTest, AllocationLimitsWorks) {
  auto* memory_request = static_cast<char*>(stack_allocator_->Allocate(memory_size_bytes_));
  ASSERT_EQ(memory_request, nullptr);
}

TEST_F(StackAllocatorTest, CantDeallocateFreeMemory) {
  stack_allocator_->Deallocate();
  auto* memory_request = static_cast<unsigned char*>(stack_allocator_->Allocate(10));
  ASSERT_EQ(memory_request, allocated_memory_);
}
