#include "stack_allocator.hpp"
#include <memory>

allocators::StackAllocator::StackAllocator(unsigned char* memory_begin_pointer, const uint64_t& memory_size_bytes) noexcept
    : begin_memory_pointer_(memory_begin_pointer),
      memory_size_bytes_(memory_size_bytes),
      top_memory_pointer_(memory_begin_pointer) {}

allocators::StackAllocator::~StackAllocator() noexcept {
  while (top_memory_pointer_ != begin_memory_pointer_) {
    Deallocate();
  }
}

void* allocators::StackAllocator::Allocate(uint64_t size_bytes) noexcept {
  if (top_memory_pointer_ + size_bytes > begin_memory_pointer_ + memory_size_bytes_) {
    return nullptr;
  }
  unsigned char* allocated_memory_begin = top_memory_pointer_;
  top_memory_pointer_ += size_bytes;

  auto* allocated_size = new(top_memory_pointer_) uint64_t();
  *allocated_size = size_bytes;
  top_memory_pointer_ += sizeof(uint64_t);

  return static_cast<void*>(allocated_memory_begin);
}

void allocators::StackAllocator::Deallocate() noexcept {
  if (top_memory_pointer_ == begin_memory_pointer_) {
    return;
  }

  top_memory_pointer_ -= sizeof(uint64_t);
  uint64_t block_size_bytes = static_cast<uint64_t>(*top_memory_pointer_);
  top_memory_pointer_ -= block_size_bytes;
}