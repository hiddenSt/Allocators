#include <gtest/gtest.h>

#include <allocators/pointer_arithmetic/pointer_arithmetic.hpp>

TEST(PointerArithmetic, ReturnsRightAdjustment) {
  allocators::PointerArithmetic pointer_arithmetic(64);
  auto* address = new unsigned char();
  std::size_t adjustment = pointer_arithmetic.GetAdjustment(address);
  std::uintptr_t aligned_address = reinterpret_cast<uintptr_t>(address) + adjustment;

  ASSERT_EQ(aligned_address%64, 0);
}

TEST(PointerArithmetic, ThrowsExceptionIfGivenAlignmentIsNotPower0f2) {
  allocators::PointerArithmetic pointer_arithmetic(5);
  auto* addr = new unsigned char();
  ASSERT_THROW(pointer_arithmetic.GetAdjustment(addr), std::runtime_error);
}

TEST(PointerArithmetic, ThrowsExceptionIfGivenAlignmentIsLessThan8) {
  allocators::PointerArithmetic pointer_arithmetic(4);
  auto* addr = new unsigned char();
  ASSERT_THROW(pointer_arithmetic.GetAdjustment(addr), std::runtime_error);
}