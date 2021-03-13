#ifndef ALLOCATORS_ALLOCATORS_POINTER_MATH_POINTER_MATH_HPP_
#define ALLOCATORS_ALLOCATORS_POINTER_MATH_POINTER_MATH_HPP_

#include <cstdint>

namespace allocators {

class PointerArithmetic {
 public:
  explicit PointerArithmetic(const std::size_t& alignment);
  ~PointerArithmetic() = default;

  std::size_t GetAdjustment(unsigned char* memory_address) const noexcept;

 private:
  std::size_t alignment_;
};

}  // namespace allocators

#endif  // ALLOCATORS_ALLOCATORS_POINTER_MATH_POINTER_MATH_HPP_
