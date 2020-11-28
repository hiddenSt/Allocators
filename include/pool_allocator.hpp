#ifndef ALLOCATORS_INCLUDE_POOL_ALLOCATOR_HPP_
#define ALLOCATORS_INCLUDE_POOL_ALLOCATOR_HPP_

#include <cstdint>

namespace allocators {

class PoolAllocator {
 public:
  explicit PoolAllocator();

  void* Allocate() noexcept;
  void Free(void* chunk_pointer) noexcept;

 private:
  struct Header {
    void* next_header;
  };

  Header* list_header_;
  uint64_t memory_size_bytes;
  void* memory_begin_pointer;
};

}  // namespace allocators

#endif  // ALLOCATORS_INCLUDE_POOL_ALLOCATOR_HPP_
