#pragma once

#include <cstdint>

#include "target.h"

class Limitter
{
  int32_t buffer_;

 public:
  void Input(int32_t input)
  {
    buffer_ = input;
  }
  int32_t Output()
  {
    return __SSAT(buffer_, 16);
  }
};