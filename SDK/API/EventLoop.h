#pragma once

#include <cstddef>
#include <cstdint>

#include "EventQueue.h"
#include "Literals.h"
#include "SystemTick.h"
#include "common.h"

template <size_t N = 32>
class EventLoop : public EventQueue<N>
{
 public:
  EventLoop()
  {
    system_events.call([this] { dispatch(); });
  }

  Callback call(Event &&events) { return this->enqueue(std::move(events)); }

  void dispatch()
  {
    while (this->get_status() == EventQueue<N>::Status::RUN)
      {
        Event events = std::move(this->dequeue());
        switch (events.cycle)
          {
            case Call::EVERY:
              if (events.counter <= 0)
                {
                  events.event();
                  events.counter = events.interval;
                }
              events.counter--;
              this->re_enqueue(std::move(events));
              break;

            case Call::STOP:
              break;

            case Call::ONCE:
              if (events.counter <= 0)
                {
                  events.event();
                }
              else
                {
                  events.counter--;
                  this->re_enqueue(std::move(events));
                }
              break;

            default:
              if (events.counter <= 0)
                {
                  events.event();
                  events.cycle--;
                  events.counter = events.interval;
                }
              events.counter--;
              this->re_enqueue(std::move(events));
              break;
          }
      }
    this->pre_process();
  }
};
