#pragma once

#include <cstdint>

#include "macro.h"
#include GEN_HEADER(TARGET, )

namespace bad
{
template <typename T>
constexpr T limit(auto&& input)
{
  return __SSAT(input, sizeof(T) * 8U);
}
}  // namespace bad
