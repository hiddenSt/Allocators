#ifndef ALLOCATORS_INCLUDE_STL_ALLOCATOR_HPP_
#define ALLOCATORS_INCLUDE_STL_ALLOCATOR_HPP_

#include <cstdint>

namespace allocators {

template <typename T, typename AllocationStrategy>
class StlAllocator {
 public:
  using value_type = T;

  explicit StlAllocator(const AllocationStrategy& allocation_strategy);

  T* allocate(std::size_t n);
  void deallocate(T* pointer, std::size_t n) noexcept;

 private:
  AllocationStrategy& allocation_strategy_;
};

template <typename T, typename AllocationStrategy>
StlAllocator<T, AllocationStrategy>::StlAllocator(const AllocationStrategy& allocation_strategy)
    : allocation_strategy_(allocation_strategy) {
}

template <typename T, typename AllocationStrategy>
T* StlAllocator<T, AllocationStrategy>::allocate(std::size_t n) {
  return static_cast<T*>(allocation_strategy_->Allocate(n * sizeof(T)));
}

template <typename T, typename AllocationStrategy>
void StlAllocator<T, AllocationStrategy>::deallocate(T* pointer, std::size_t n) noexcept {
  allocation_strategy_->Free(static_cast<void*>(pointer));
}

}  // namespace allocators

#endif  // ALLOCATORS_INCLUDE_STL_ALLOCATOR_HPP_
