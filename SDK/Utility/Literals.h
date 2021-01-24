#pragma once

#include <cstdint>

using ms_t = int16_t;

consteval ms_t operator""ms(unsigned long long ms)
{
  return ms_t(ms);
}

consteval uint32_t operator"" Hz(unsigned long long Hz)
{
  return uint32_t(Hz);
}
consteval uint32_t operator"" kHz(unsigned long long kHz)
{
  return uint32_t(kHz) * 1000;
}
consteval uint32_t operator"" MHz(unsigned long long MHz)
{
  return uint32_t(MHz) * 1000'000;
}

// class hz_t {
//    public:
//     int a_;
//     constexpr hz_t(int a) { a_ = 1 / a; }
//     constexpr operator int() { return a_; }
// };