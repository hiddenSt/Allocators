#ifndef ALLOCATORS__STACK_ALLOCATOR_HPP_
#define ALLOCATORS__STACK_ALLOCATOR_HPP_

#include <cstdint>
namespace allocators {

class StackAllocator {
 public:
  explicit StackAllocator(unsigned char* memory_begin_pointer, const uint64_t& memory_size_bytes) noexcept;
  ~StackAllocator() noexcept;
  StackAllocator(const StackAllocator& other) noexcept = delete;

  void* Allocate(uint64_t size_bytes) noexcept;
  void Deallocate() noexcept;

 private:
  unsigned char* const memory_begin_pointer_;
  unsigned char* memory_top_pointer_;
  uint64_t memory_size_bytes_;
};

}

#endif //ALLOCATORS__STACK_ALLOCATOR_HPP_
