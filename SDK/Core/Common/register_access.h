#pragma once

#include "cmsis_gcc.h"

#define SET_BIT(REG, BIT) ((REG) = (REG) | (BIT))

#define CLEAR_BIT(REG, BIT) ((REG) = (REG) & ~(BIT))

#define READ_BIT(REG, BIT) ((REG) & (BIT))

#define CLEAR_REG(REG) ((REG) = (0x0))

#define WRITE_REG(REG, VAL) ((REG) = (VAL))

#define READ_REG(REG) ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK) WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

#define POSITION_VAL(VAL) (__CLZ(__RBIT(VAL)))

typedef enum
{
  RESET = 0U,
  SET = !RESET
} FlagStatus,
    ITStatus;

typedef enum
{
  DISABLE = 0U,
  ENABLE = !DISABLE
} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum
{
  SUCCESS = 0U,
  ERROR = !SUCCESS
} ErrorStatus;

// #include <bit>
// #include <cstddef>
// #include <cstdint>

// template <size_t bits>
// constexpr uint32_t reverse_bits(uint32_t value)
// {
//   uint32_t result = 0;
//   // for (size_t i = 0, j = bits - 1; i < bits; ++i, --j) {
//   //     result |= ((value & (1 << j)) >> j) << i;
//   // }
//   // return result;
//   uint32_t s = bits - 1U;
//   result = value; /* r will be reversed bits of v; first get LSB of v */
//   for (value >>= 1U; value != 0U; value >>= 1U)
//     {
//       result <<= 1U;
//       result |= value & 1U;
//       s--;
//     }
//   result <<= s; /* shift when v's highest bits are zero */
//   return result;
// }

// #define POSITION_VAL(VAL) (std::countl_zero(reverse_bits<32>(VAL)))

// constexpr uint32_t POSITION_VAL(uint32_t value)
// {
//   return std::countl_zero(reverse_bits<32>(value));
// }

// static inline uint32_t POSITION_VAL(uint32_t value)
// {
//   return __CLZ(__RBIT(value));
// }