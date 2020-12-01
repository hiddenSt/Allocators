#ifndef ALLOCATORS_INCLUDE_POOL_ALLOCATOR_HPP_
#define ALLOCATORS_INCLUDE_POOL_ALLOCATOR_HPP_

#include <cstdint>

namespace allocators {

class PoolAllocator {
 public:
  explicit PoolAllocator(unsigned char* memory_begin_pointer, const uint64_t& memory_size_bytes,
                         const uint64_t& block_size_bytes);
  ~PoolAllocator();

  void* Allocate() noexcept;
  void Free(void* memory_block_pointer);

 private:
  struct MemoryBlock {
    MemoryBlock* next_block = nullptr;
  };

  void ValidatePointerToFree(void* pointer) const;
  void ValidateGivenPointerToMemoryBegin() const;

  const std::size_t block_size_bytes_;
  MemoryBlock* header_;
  uint64_t memory_size_bytes_;
  unsigned char* begin_memory_pointer_;
};

}  // namespace allocators

#endif  // ALLOCATORS_INCLUDE_POOL_ALLOCATOR_HPP_
