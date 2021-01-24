#pragma once

#include <cstddef>
#include <cstdint>

#include "Literals.h"
#include "common.h"

enum Call : int32_t
{
  PEND = -2,
  EVERY = -1,
  STOP = 0,
  ONCE = 1
};

struct Event
{
  Callback event = [] {};
  int8_t cycle = Call::ONCE;
  ms_t counter = 0ms;
  ms_t interval = 0ms;
};

template <size_t N>
class EventQueue
{
 private:
  Event _queue[N];
  size_t _full = N - 1;
  size_t _head = 0;
  size_t _tail = 0;
  size_t _re_tail = 0;

 public:
  enum Status
  {
    EMPTY,
    RUN,
    FULL
  } _state
      = EMPTY;

  Callback enqueue(Event &&e)
  {
    _state = RUN;
    _queue[_tail & _full] = e;
    _tail = (_tail + 1) & _full;
    return e.event;
  }

  Callback re_enqueue(Event &&e)
  {
    _queue[(_tail + _re_tail) & _full] = e;
    _re_tail = (_re_tail + 1);
    return e.event;
  }

  Event dequeue()
  {
    if ((_tail - ((_head + 1) & _full)) == 0)
      {
        _state = EMPTY;
      }
    else
      {
        _state = RUN;
      }
    size_t i = _head & _full;
    _head = (_head + 1) & _full;
    return _queue[i];
  }

  void pre_process()
  {
    if (1 <= _re_tail)
      {
        _state = RUN;
        _tail = (_tail + (_re_tail & _full)) & _full;
        _re_tail = 0;
      }
  }

  void clear() { _tail = _head; }

  Status get_status() { return _state; }

  void stop(Callback func)
  {
    for (size_t i = 0; i < _full; i++)
      {
        if (_queue[i].event == func)
          {
            _queue[i].cycle = Call::STOP;
          }
      }
  }
};