#include "pool_allocator.hpp"

#include <stdexcept>

namespace allocators {

PoolAllocator::PoolAllocator(unsigned char* memory_begin_pointer, const uint64_t& memory_size_bytes,
                             const uint64_t& block_size_bytes)
    : begin_memory_pointer_(memory_begin_pointer),
      memory_size_bytes_(memory_size_bytes),
      header_(nullptr),
      block_size_bytes_(block_size_bytes) {
  ValidateGivenPointerToMemoryBegin();

  std::size_t free_block_count = memory_size_bytes_ / block_size_bytes_;
  unsigned char* block_ptr = begin_memory_pointer_;
  header_ = new (block_ptr) MemoryBlock();
  MemoryBlock* tmp = header_;
  for (std::size_t i = 1; i < free_block_count; ++i) {
    block_ptr += block_size_bytes_;
    tmp->next_block = new (block_ptr) MemoryBlock();
    tmp = tmp->next_block;
  }
}

void* PoolAllocator::Allocate() noexcept {
  std::lock_guard<std::mutex> lock(alloc_mutex_);

  // Critical section

  if (header_ == nullptr) {
    return nullptr;
  }

  auto* allocated_memory = header_;
  header_ = header_->next_block;
  header_->~MemoryBlock();
  return reinterpret_cast<void*>(allocated_memory);
  // End of critical section
}

void PoolAllocator::Free(void* memory_block_pointer) {
  ValidatePointerToFree(memory_block_pointer);

  std::lock_guard<std::mutex> lock(alloc_mutex_);

  // Critical section
  auto* free_block = new (memory_block_pointer) MemoryBlock();
  free_block->next_block = header_;
  header_ = free_block;
  // End of critical section
}

allocators::PoolAllocator::~PoolAllocator() {
  auto tmp = header_;
  while (tmp != nullptr) {
    auto tmp1 = tmp;
    tmp1->~MemoryBlock();
    tmp = tmp->next_block;
  }
}

void PoolAllocator::ValidatePointerToFree(void* pointer) const {
  auto* memory_block_uc_ptr = static_cast<unsigned char*>(pointer);
  auto memory_block_uint_ptr = reinterpret_cast<std::uintptr_t>(pointer);
  auto begin_memory_pointer_uint_ptr = reinterpret_cast<std::uintptr_t>(begin_memory_pointer_);

  if (memory_block_uc_ptr >= begin_memory_pointer_ + memory_size_bytes_ ||
      memory_block_uc_ptr < begin_memory_pointer_ ||
      (memory_block_uint_ptr - begin_memory_pointer_uint_ptr) % block_size_bytes_ != 0) {
    throw std::runtime_error("Invalid pointer.");
  }
}

void PoolAllocator::ValidateGivenPointerToMemoryBegin() const {
  if (memory_size_bytes_ % block_size_bytes_ != 0) {
    throw std::logic_error("Given memory arena size does not multiple of given block size.");
  }

  if (block_size_bytes_ > memory_size_bytes_) {
    throw std::logic_error("Given memory block size is more than memory arena size.");
  }

  if (begin_memory_pointer_ == nullptr) {
    throw std::logic_error("Given memory begin pointer is nullptr.");
  }

  if (memory_size_bytes_ == 0) {
    throw std::logic_error("Given memory size is 0.");
  }

  if (block_size_bytes_ < sizeof(MemoryBlock)) {
    throw std::logic_error("Given block size is less than 8 size of MemoryBlock.");
  }
}

PoolAllocator::PoolAllocator(PoolAllocator&& other) noexcept
    : memory_size_bytes_(other.memory_size_bytes_),
      block_size_bytes_(other.block_size_bytes_),
      begin_memory_pointer_(other.begin_memory_pointer_),
      header_(other.header_) {
  other.memory_size_bytes_ = 0;
  other.header_ = nullptr;
  other.begin_memory_pointer_ = nullptr;
}

}  // namespace allocators