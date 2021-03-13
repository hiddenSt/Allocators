#include "pointer_arithmetic.hpp"

namespace allocators {

PointerArithmetic::PointerArithmetic(const std::size_t& alignment) : alignment_(alignment) {
}

std::size_t PointerArithmetic::GetAdjustment(unsigned char* memory_address) const noexcept {
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

}  // namespace allocators