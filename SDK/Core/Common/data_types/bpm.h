#pragma once

#include <cstdint>

namespace bad
{
class period
{
 private:
 public:
  class msec
  {
   private:
    float _value;

   public:
    constexpr msec(float value) : _value(value) {}
    operator int() const { return 100; }
  };
};

class bpm
{
 private:
  float _value;

 public:
  consteval bpm(float &&value) : _value(value) {}
  consteval bpm(const bpm &rhs);
  // consteval bpm &operator=(const bpm &rhs)
  // {
  //   // bpm(rhs.get());
  //   return *this;
  // }
  consteval       operator float() const { return _value; }
  consteval float get() { return _value; }
  consteval void  set(float value) { _value = value; }

  consteval operator period::msec() const { return 60000 / _value; }
};
}  // namespace bad

consteval bad::period::msec operator""ms(unsigned long long ms)
{
  return bad::period::msec(ms);
}
consteval bad::period::msec operator""ms(long double ms)
{
  return bad::period::msec(ms);
}

consteval bad::bpm operator"" bpm(unsigned long long value)
{
  return bad::bpm(value);
}
consteval bad::bpm operator"" bpm(long double value)
{
  return bad::bpm(value);
}

using Voltage = float;

consteval Voltage operator"" V(unsigned long long value)
{
  return Voltage(value / 3.3);
}
consteval Voltage operator"" V(long double value)
{
  return Voltage(value / 3.3);
}

void test()
{
  constexpr auto              tempo1 = 120.0bpm;
  constexpr bad::bpm          tempo2 = 120.0bpm;
  constexpr bad::period::msec tempo3 = 120.0bpm;

  constexpr Voltage volt = 3.3V;
}
