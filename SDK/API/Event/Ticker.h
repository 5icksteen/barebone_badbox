#pragma once

#include <cstdint>
#include "second.h"

class Ticker
{
 private:
  uint32_t _count = 0ms;

 public:
  void     reset() { _count = 0ms; }
  void     tick() { _count++; }
  uint32_t read_ms() { return _count; }
};
