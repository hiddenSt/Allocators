#include "pool_allocator.hpp"

#include <stdexcept>

allocators::PoolAllocator::PoolAllocator(unsigned char *memory_begin_pointer,
                                         const uint64_t &memory_size_bytes,
                                         const uint64_t &block_size_bytes)
    : begin_memory_pointer_(memory_begin_pointer),
      memory_size_bytes_(memory_size_bytes),
      header_(nullptr),
      block_size_bytes_(block_size_bytes) {
  if (memory_size_bytes_ % block_size_bytes_ != 0) {
    throw std::logic_error("Given memory arena size does not multiple of given block size.");
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

  std::size_t free_block_count = memory_size_bytes_ / block_size_bytes_;
  unsigned char *block_ptr = begin_memory_pointer_;
  header_ = new (block_ptr) MemoryBlock();
  MemoryBlock *tmp = header_;
  for (std::size_t i = 1; i < free_block_count; ++i) {
    block_ptr += block_size_bytes_;
    tmp->next_block = new (block_ptr) MemoryBlock();
    tmp = tmp->next_block;
  }
}

void *allocators::PoolAllocator::Allocate() noexcept {
  if (header_ == nullptr) {
    return nullptr;
  }

  auto *allocated_memory = header_;
  header_ = header_->next_block;
  header_->~MemoryBlock();
  return reinterpret_cast<void*>(allocated_memory);
}

void allocators::PoolAllocator::Free(void* memory_block_pointer)  {
  auto* memory_block_uc_ptr = static_cast<unsigned char*>(memory_block_pointer);
  auto memory_block_uint_ptr = reinterpret_cast<std::uintptr_t>(memory_block_pointer);

  // TODO: check for pointer correctness
  if (memory_block_uc_ptr > begin_memory_pointer_ + memory_size_bytes_ ||
      memory_block_uc_ptr < begin_memory_pointer_ || memory_block_uint_ptr % block_size_bytes_ != 0) {
    throw std::runtime_error("Invalid pointer");
  }

  auto *free_block = new (memory_block_pointer) MemoryBlock();
  free_block->next_block = header_;
  header_ = free_block;
}

allocators::PoolAllocator::~PoolAllocator() {
  auto tmp = header_;
  while (tmp != nullptr) {
    auto tmp1 = tmp;
    tmp1->~MemoryBlock();
    tmp = tmp->next_block;
  }
}
