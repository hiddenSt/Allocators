#include "pointer_arithmetic.hpp"

#include <stdexcept>

namespace allocators {

PointerArithmetic::PointerArithmetic(std::size_t alignment) : alignment_(alignment) {
}

std::size_t PointerArithmetic::GetAdjustment(const unsigned char* memory_address) const {
  ValidateAlignmentIsPowerOfTwo(alignment_);
  ValidateAlignmentIsGreaterOrEqualThan8(alignment_);

  auto unaligned_memory = reinterpret_cast<std::uintptr_t>(memory_address);
  std::size_t mask = ~(alignment_ - 1);
  std::uintptr_t masked_memory = mask & unaligned_memory;

  std::uintptr_t aligned_memory_address = 0;
  std::size_t adjustment = 0;

  if (unaligned_memory == masked_memory) {
    return adjustment;
  } else {
    aligned_memory_address = (unaligned_memory + alignment_ - 1) & mask;
    adjustment = static_cast<std::size_t>(aligned_memory_address - unaligned_memory);
    return adjustment;
  }
}

void PointerArithmetic::ValidateAlignmentIsPowerOfTwo(std::size_t alignment) const {
  if ((alignment & alignment - 1) != 0) {
    throw std::runtime_error("Alignment has to be power of 2");
  }
}
void PointerArithmetic::ValidateAlignmentIsGreaterOrEqualThan8(std::size_t alignment) const {
  if (alignment < 8) {
    throw std::runtime_error("Alignment has to be >= 8");
  }
}

}  // namespace allocators