#ifndef ALLOCATORS_ALLOCATORS_POINTER_MATH_POINTER_MATH_HPP_
#define ALLOCATORS_ALLOCATORS_POINTER_MATH_POINTER_MATH_HPP_

#include <cstdint>

namespace allocators {

class PointerMath {
 public:
  std::uintptr_t GetAlignedAddress();
};

}  // namespace allocators

#endif  // ALLOCATORS_ALLOCATORS_POINTER_MATH_POINTER_MATH_HPP_
