#pragma once

#include "StaticEvent.h"
#include "Ticker.h"
#include "macro.h"
#include GEN_HEADER(TARGET, )
#include GEN_HEADER(TARGET_BASE, _bus)
#include GEN_HEADER(TARGET_BASE, _tim)

Ticker      system_timer;
StaticEvent system_events;

void SysTick_Handler()
{
  SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
  system_timer.tick();
}

void PendSV_Handler() { system_events.dispatch(); }

class SystemTimer
{
 private:
  uint32_t _start_time = 0ms;
  uint32_t _time = 0ms;
  bool     _status = false;

 public:
  void start()
  {
    // _start_time = system_timer.read_ms();
    _status = true;
  }
  void stop()
  {
    _time += read();
    _status = false;
  }
  void reset()
  {
    _start_time = system_timer.read_ms();
    _time = 0ms;
  }
  ms_t read()
  {
    if (_status == true)
      {
        uint32_t now = system_timer.read_ms();
        // if (_start = true)
        //   {
        //     _start_time = now - 1ms;
        //     _start = false;
        //   }
        if (_start_time <= now)
          return now - _start_time;
        else
          return (UINT32_MAX - _start_time) + now;
      }
    else
      {
        return 0;
      }
  }
};