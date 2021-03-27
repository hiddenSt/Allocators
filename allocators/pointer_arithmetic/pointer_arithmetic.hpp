#ifndef ALLOCATORS_ALLOCATORS_POINTER_MATH_POINTER_MATH_HPP_
#define ALLOCATORS_ALLOCATORS_POINTER_MATH_POINTER_MATH_HPP_

#include <cstdint>

namespace allocators {

class PointerArithmetic {
 public:
  explicit PointerArithmetic(std::size_t alignment);
  ~PointerArithmetic() = default;

  std::size_t GetAdjustment(const unsigned char* memory_address) const;

 private:
  void ValidateAlignmentIsPowerOfTwo(std::size_t alignment) const;
  void ValidateAlignmentIsGreaterOrEqualThan8(std::size_t alignment) const;
  std::size_t alignment_;
};

}  // namespace allocators

#endif  // ALLOCATORS_ALLOCATORS_POINTER_MATH_POINTER_MATH_HPP_
