#include "stack_allocator.hpp"

#include <memory>
#include <cstdint>

allocators::StackAllocator::StackAllocator(unsigned char* memory_begin_pointer,
                                           const uint64_t& memory_size_bytes) noexcept
    : begin_memory_pointer_(memory_begin_pointer),
      memory_size_bytes_(memory_size_bytes),
      top_memory_pointer_(memory_begin_pointer) {
}

allocators::StackAllocator::~StackAllocator() noexcept {
  top_memory_pointer_ = nullptr;
  begin_memory_pointer_ = nullptr;
  memory_size_bytes_ = 0;
}

void* allocators::StackAllocator::Allocate(uint64_t size_bytes, std::size_t alignment) noexcept {
  // TODO: need to add check if alignment is power of 2
  void* unaligned_memory = AllocateUnaligned(size_bytes);

  if (unaligned_memory == nullptr) {
    return nullptr;
  }

  auto unaligned_memory_ptr = reinterpret_cast<std::uintptr_t>(unaligned_memory);
  std::size_t mask = ~(alignment - 1);
  if (unaligned_memory_ptr == (mask & unaligned_memory_ptr)) {
    return unaligned_memory;
  }

  std::uintptr_t aligned_memory_address = (unaligned_memory_ptr + alignment - 1) & mask;
  // TODO: need to save alignment adjustment for correct free
  return reinterpret_cast<void*>(aligned_memory_address);
}

void allocators::StackAllocator::Free() noexcept {
  if (top_memory_pointer_ == begin_memory_pointer_) {
    return;
  }

  top_memory_pointer_ -= sizeof(uint64_t);
  auto block_size_bytes = static_cast<uint64_t>(*top_memory_pointer_);
  top_memory_pointer_ -= block_size_bytes;
}

allocators::StackAllocator::StackAllocator(allocators::StackAllocator&& other) noexcept
    : begin_memory_pointer_(other.begin_memory_pointer_),
      top_memory_pointer_(other.top_memory_pointer_),
      memory_size_bytes_(other.memory_size_bytes_) {
  other.begin_memory_pointer_ = nullptr;
  other.top_memory_pointer_ = nullptr;
  other.memory_size_bytes_ = 0;
}

void* allocators::StackAllocator::AllocateUnaligned(uint64_t size_bytes) noexcept {
  if (top_memory_pointer_ + size_bytes + sizeof(uint64_t) >
      begin_memory_pointer_ + memory_size_bytes_) {
    return nullptr;
  }

  /*unsigned char* allocated_memory_begin = top_memory_pointer_;
  top_memory_pointer_ += size_bytes;

  auto* allocated_size = new (top_memory_pointer_) uint64_t();
  *allocated_size = size_bytes;
  top_memory_pointer_ += sizeof(uint64_t);*/

  return static_cast<void*>(allocated_memory_begin);
}
