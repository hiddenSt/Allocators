#include "stack_allocator.hpp"

#include <cstdint>
#include <stdexcept>

namespace allocators {

StackAllocator::StackAllocator(unsigned char* memory_begin_pointer,
                                           const uint64_t& memory_size_bytes)
    : begin_memory_pointer_(memory_begin_pointer),
      memory_size_bytes_(memory_size_bytes),
      top_memory_pointer_(memory_begin_pointer) {
  if (begin_memory_pointer_ == nullptr) {
    throw std::logic_error("Given memory begin pointer is nullptr.");
  }

  if (memory_size_bytes_ == 0) {
    throw std::logic_error("Given memory size is 0.");
  }
}

StackAllocator::StackAllocator(StackAllocator&& other) noexcept
    : begin_memory_pointer_(other.begin_memory_pointer_),
      top_memory_pointer_(other.top_memory_pointer_),
      memory_size_bytes_(other.memory_size_bytes_) {
  other.begin_memory_pointer_ = nullptr;
  other.top_memory_pointer_ = nullptr;
  other.memory_size_bytes_ = 0;
}

allocators::StackAllocator::~StackAllocator() noexcept {
  top_memory_pointer_ = nullptr;
  begin_memory_pointer_ = nullptr;
  memory_size_bytes_ = 0;
}

void* StackAllocator::Allocate(const uint64_t& size_bytes,
                                           const std::size_t& alignment) {
  ValidateAlignmentIsPowerOfTwo(alignment);

  if (size_bytes == 0) {
    throw std::logic_error("Can not allocate 0 bytes.");
  }

  std::size_t adjustment = GetAdjustmentToAlignMemoryAddress(top_memory_pointer_, alignment);
  auto unaligned_memory = reinterpret_cast<std::uintptr_t>(top_memory_pointer_);

  std::uintptr_t aligned_memory_address = unaligned_memory + adjustment;
  if (top_memory_pointer_ + adjustment + size_bytes + sizeof(uint64_t) >
      begin_memory_pointer_ + memory_size_bytes_) {
    return nullptr;
  }

  top_memory_pointer_ += adjustment + size_bytes;
  auto* block_size = new (top_memory_pointer_) uint64_t();
  *block_size = adjustment + size_bytes;
  top_memory_pointer_ += sizeof(uint64_t);

  return reinterpret_cast<void*>(aligned_memory_address);
}

void StackAllocator::Free() noexcept {
  if (top_memory_pointer_ == begin_memory_pointer_) {
    return;
  }

  top_memory_pointer_ -= sizeof(uint64_t);
  auto block_size_bytes = static_cast<uint64_t>(*top_memory_pointer_);
  top_memory_pointer_ -= block_size_bytes;
}

void StackAllocator::ValidateAlignmentIsPowerOfTwo(const size_t& alignment) const {
  if ((alignment & alignment - 1) != 0) {
    throw std::runtime_error("Alignment has to be power of 2");
  }
}

std::size_t StackAllocator::GetAdjustmentToAlignMemoryAddress(
    unsigned char* memory_address, const size_t& alignment) const noexcept {
  auto unaligned_memory = reinterpret_cast<std::uintptr_t>(memory_address);
  std::size_t mask = ~(alignment - 1);
  std::uintptr_t masked_memory = mask & unaligned_memory;

  std::uintptr_t aligned_memory_address = 0;
  std::size_t adjustment = 0;

  if (unaligned_memory == masked_memory) {
    return adjustment;
  } else {
    aligned_memory_address = (unaligned_memory + alignment - 1) & mask;
    adjustment = static_cast<std::size_t>(aligned_memory_address - unaligned_memory);
    return adjustment;
  }
}

}  // namespace allocators