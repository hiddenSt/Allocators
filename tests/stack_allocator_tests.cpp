#include "gtest/gtest.h"
#include "stack_allocator.hpp"

class StackAllocatorTest : public ::testing::Test {
 protected:
  void SetUp() override {
    allocated_memory_ = new unsigned char[memory_size_bytes_];
    stack_allocator_ = new allocators::StackAllocator(allocated_memory_, memory_size_bytes_);
  }

  const uint64_t memory_size_bytes_ = 80;
  std::size_t alignment_ = 8;
  unsigned char* allocated_memory_;
  allocators::StackAllocator* stack_allocator_;
};

TEST_F(StackAllocatorTest, AllocationWorks) {
  auto* memory_request = static_cast<unsigned char*>(stack_allocator_->Allocate(5, alignment_));
  ASSERT_NE(memory_request, nullptr);
}

TEST_F(StackAllocatorTest, DeallocationWorks) {
  auto* memory_request_1 = static_cast<unsigned char*>(stack_allocator_->Allocate(5, alignment_));
  ASSERT_NE(memory_request_1, nullptr);

  stack_allocator_->Free();

  auto* memory_request_2 = static_cast<unsigned char*>(stack_allocator_->Allocate(10, alignment_));
  ASSERT_EQ(memory_request_2, memory_request_1);
}

TEST_F(StackAllocatorTest, MultipleAllocationsWorks) {
  auto* memory_request_1 = static_cast<unsigned char*>(stack_allocator_->Allocate(5, alignment_));
  ASSERT_NE(memory_request_1, nullptr);

  auto* memory_request_2 = static_cast<unsigned char*>(stack_allocator_->Allocate(5, alignment_));
  ASSERT_NE(memory_request_2, nullptr);

  ASSERT_GT(memory_request_2, memory_request_1);
}

TEST_F(StackAllocatorTest, AllocationLimitsWorks) {
  auto* memory_request =
      static_cast<unsigned char*>(stack_allocator_->Allocate(memory_size_bytes_, alignment_));
  ASSERT_EQ(memory_request, nullptr);
}

TEST_F(StackAllocatorTest, CantDeallocateFreeMemory) {
  stack_allocator_->Free();
  auto* memory_request = static_cast<unsigned char*>(stack_allocator_->Allocate(10, alignment_));
  ASSERT_EQ(memory_request, allocated_memory_);
}

TEST_F(StackAllocatorTest, AllocateReturnsCorrectAlignedPointer) {
  std::size_t mask = ~(alignment_ - 1);
  auto* memory_request = stack_allocator_->Allocate(10, alignment_);
  auto memory_ptr = reinterpret_cast<std::uintptr_t>(memory_request);
  ASSERT_EQ(memory_ptr & mask, memory_ptr) << std::hex << memory_ptr;
}

TEST_F(StackAllocatorTest, ThrowsRunTimeErrorIfAlignmentIsNotPowerOf2) {
  std::size_t alignment = 5;
  ASSERT_THROW(stack_allocator_->Allocate(10, alignment), std::runtime_error);
}