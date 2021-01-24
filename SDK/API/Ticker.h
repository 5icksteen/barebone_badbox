#pragma once

#include "Literals.h"
#include "common.h"
#include "target.h"

class Ticker
{
 private:
  ms_t _count;

 public:
  Ticker() { this->reset(); }

  void reset()
  {
    __disable_irq();
    _count = 0ms;
    __enable_irq();
  }

  void tick() { _count++; }

  ms_t read_ms()
  {
    __disable_irq();
    auto count = _count;
    __enable_irq();
    return count;
  }

  void dispatch(Callback &&func)
  {
    if (read_ms() >= 1ms)
      {
        func();
        this->reset();
      }
  }
};

// extern Ticker ticker;