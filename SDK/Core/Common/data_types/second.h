#pragma once

#include <cstdint>

using ms_t = int16_t;

consteval ms_t operator""ms(unsigned long long ms)
{
  return ms_t(ms);
}
