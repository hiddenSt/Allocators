#include "stack_allocator.hpp"
#include <memory>

allocators::StackAllocator::StackAllocator(unsigned char* memory_begin_pointer, const uint64_t& memory_size_bytes) noexcept
    : memory_begin_pointer_(memory_begin_pointer),
      memory_size_bytes_(memory_size_bytes),
      memory_top_pointer_(memory_begin_pointer) {}

allocators::StackAllocator::~StackAllocator() noexcept {
  while (memory_top_pointer_ != memory_begin_pointer_) {
    Deallocate();
  }
}

void* allocators::StackAllocator::Allocate(uint64_t size_bytes) noexcept {
  if (memory_top_pointer_ + size_bytes > memory_begin_pointer_ + memory_size_bytes_) {
    return nullptr;
  }
  unsigned char* allocated_memory_begin = memory_top_pointer_;
  memory_top_pointer_ += size_bytes;

  auto* allocated_size = new(memory_top_pointer_) uint64_t();
  *allocated_size = size_bytes;
  memory_top_pointer_ += sizeof(uint64_t);

  return static_cast<void*>(allocated_memory_begin);
}

void allocators::StackAllocator::Deallocate() noexcept {
  if (memory_top_pointer_ == memory_begin_pointer_) {
    return;
  }

  memory_top_pointer_ -= sizeof(uint64_t);
  uint64_t block_size_bytes = static_cast<uint64_t>(*memory_top_pointer_);
  memory_top_pointer_ -= block_size_bytes;
}