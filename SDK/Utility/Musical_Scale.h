#pragma once

#include <cmath>
#include <cstdint>

template <int N>
struct musical_scale
{
  uint32_t m = 1'191;
  uint32_t n = 0x10'000 - m;  // 65536-m
  uint8_t array[N];
  consteval led_number_array() : array()
  {
    for (i = 0; i <= N; i++)
      {
        array[i] = (uint32_t)round(n / pow(2.0, i / 12.));
      }
  }
};