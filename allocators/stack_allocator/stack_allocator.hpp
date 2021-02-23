#ifndef ALLOCATORS__STACK_ALLOCATOR_HPP_
#define ALLOCATORS__STACK_ALLOCATOR_HPP_

#include <cstdint>

namespace allocators {

class StackAllocator {
 public:
  explicit StackAllocator(unsigned char* memory_begin_pointer, const uint64_t& memory_size_bytes);
  ~StackAllocator() noexcept;
  StackAllocator(StackAllocator&& other) noexcept;
  StackAllocator(const StackAllocator& other) noexcept = delete;

  StackAllocator& operator=(const StackAllocator& other) = delete;
  StackAllocator& operator=(StackAllocator&& other) = delete;

  void* Allocate(const uint64_t& size_bytes, const std::size_t& alignment);
  void Free() noexcept;

 private:
  void ValidateAlignmentIsPowerOfTwo(const std::size_t& alignment) const;
  std::size_t GetAdjustmentToAlignMemoryAddress(unsigned char* memory_address,
                                                const std::size_t& alignment) const noexcept;

  unsigned char* begin_memory_pointer_;
  unsigned char* top_memory_pointer_;
  uint64_t memory_size_bytes_;
};

}  // namespace allocators

#endif
