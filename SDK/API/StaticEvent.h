#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

#include "Literals.h"
#include "common.h"

template <size_t N = 32>
class StaticEvent
{
 private:
  Callback _queue[N] = {};
  size_t _count = 0;

 public:
  StaticEvent()
  {
    for (size_t i = 0; i < N; i++)
      {
        _queue[i] = [] {};
      }
  }
  void call(Callback &&events)
  {
    if (_count < N)
      {
        _queue[_count] = std::move(events);
        _count++;
      }
  }

  void dispatch()
  {
    for (size_t i = 0; i < N; i++)
      {
        _queue[i]();
      }
  }
};
