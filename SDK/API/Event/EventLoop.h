#pragma once

#include <cstddef>
#include <cstdint>

#include "EventQueue.h"
#include "SystemTick.h"
#include "common.h"
#include "second.h"

extern StaticEvent system_events;

template <size_t N = 64>
class EventLoop : public EventQueue<N>
{
 public:
  EventLoop()
  {
    system_events.call([this] { dispatch(); });
  }

  EventID call(Event &&events) { return this->enqueue(std::move(events)); }

  void dispatch()
  {
    while (this->get_status() == EventQueue<N>::Status::RUN)
      {
        Event events = std::move(this->dequeue());
        switch (events.cycle)
          {
            case Event::Call::PEND:
              this->repeat_enqueue(std::move(events));
              break;

            case Event::Call::EVERY:
              if (events.counter <= 0)
                {
                  events.event();
                  events.counter = events.interval;
                }
              events.counter--;
              this->repeat_enqueue(std::move(events));
              break;

            case Event::Call::STOP:
              break;

            case Event::Call::ONCE:
              if (events.counter <= 0)
                {
                  events.event();
                }
              else
                {
                  events.counter--;
                  this->repeat_enqueue(std::move(events));
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
              this->repeat_enqueue(std::move(events));
              break;
          }
      }
    this->repeat_process();
  }
};
