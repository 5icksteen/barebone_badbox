#pragma once

#include <cstdint>

consteval uint32_t operator""Hz(unsigned long long Hz)
{
  return uint32_t(Hz);
}
consteval float operator""Hz(long double Hz)
{
  return float(Hz);
}
consteval uint32_t operator""kHz(unsigned long long kHz)
{
  return uint32_t(kHz) * 1000;
}
consteval float operator""kHz(long double kHz)
{
  return float(kHz) * 1000.0f;
}
consteval uint32_t operator""MHz(unsigned long long MHz)
{
  return uint32_t(MHz) * 1000'000;
}
consteval float operator""MHz(long double MHz)
{
  return float(MHz) * 1000'000.0f;
}


// class hz_t {
//    public:
//     int a_;
//     constexpr hz_t(int a) { a_ = 1 / a; }
//     constexpr operator int() { return a_; }
// };

// consteval float operator""MHz(long double MHz)
// {
//   return float(MHz) * 1000'000.0f;
// }


// constexpr size_t operator""_hash (const char* str, std::size_t length) {
//     return std::hash<std::string>()(str);
// }

// size_t hash = "TEST"_hash;