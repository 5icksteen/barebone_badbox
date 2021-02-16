#pragma once

#include <cstddef>
#include <cstdint>

namespace bad
{
constexpr bool is_pow2(auto x)
{
  if (x == 0) { return false; }
  return (x & (x - 1)) == 0;
}
}  // namespace bad
