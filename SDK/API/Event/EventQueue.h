#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <vector>

#include "common.h"
#include "counter.h"
#include "math.h"
#include "second.h"

constexpr bad::counter<__COUNTER__, 1> _EventID;
#define EVENT_ID _EventID.next<__COUNTER__>()

using EventID = uint8_t;
struct Event
{
  enum Call
  {
    PEND = -2,
    EVERY = -1,
    STOP = 0,
    ONCE = 1
  };
  Callback event = [] {};
  int8_t   cycle = Call::ONCE;
  ms_t     counter = 0ms;
  ms_t     interval = 0ms;
  EventID  id = 0;
};

template <size_t N = 64>
class EventQueue
{
 private:
  std::vector<Event> _queue = std::vector<Event>(N);
  size_t             _full = N - 1;
  size_t             _head = 0;
  size_t             _tail = 0;
  size_t             _repeat_tail = 0;

 public:
  static_assert(bad::is_pow2(N), "Template parameter N must be a power of 2");
  enum Status
  {
    EMPTY,
    RUN,
    FULL
  } _state
      = EMPTY;

  EventID enqueue(Event &&e)
  {
    _state = RUN;
    _queue[_tail] = e;
    _tail = next(_tail);
    return e.id;
  }

  EventID repeat_enqueue(Event &&e)
  {
    _queue[circulation(_tail + _repeat_tail)] = e;
    _repeat_tail = next(_repeat_tail);
    return e.id;
  }

  Event dequeue()
  {
    auto i = _head;
    _head = next(_head);
    if (_tail - _head == 0)
      {
        _state = EMPTY;
      }
    else
      {
        _state = RUN;
      }
    return _queue[i];
  }

  size_t circulation(size_t i) { return i & _full; }
  size_t next(size_t i) { return circulation(++i); }

  void repeat_process()
  {
    if (_repeat_tail)
      {
        _state = RUN;
        _tail = circulation(_tail + _repeat_tail);
        _repeat_tail = 0;
      }
  }

  void clear() { _tail = _head; }

  Status get_status() { return _state; }

  void cancel(EventID id)
  {
    for (auto &e : _queue)
      if (e.id == id) e.cycle = Event::Call::STOP;
  }
};