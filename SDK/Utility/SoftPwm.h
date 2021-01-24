#pragma once

#include <stdint.h>

class SoftPwm
{
 private:
  int32_t count_ = 0;
  int32_t autoreload_;
  int32_t compare_ = 0;
  bool state_ = 0;

 public:
  // SoftPwm(int32_t resolution) {
  //     autoreload_ = resolution;
  // }

  void init(int32_t resolution)
  {
    autoreload_ = resolution;
    count_ = 0;
  }

  void write(int32_t brightness)
  {
    compare_ = autoreload_ - brightness;
  }

  bool read()
  {
    return state_;
  }

  int32_t scan()
  {
    state_ = count_ < compare_ ? false : true;
    return count_ < autoreload_ - 1 ? count_++ : count_ = 0;
  }
};
