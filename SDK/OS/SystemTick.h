#pragma once

#include "StaticEvent.h"
#include "Ticker.h"

Ticker system_tick;
StaticEvent static_event;

void SysTick_Handler()
{
  system_tick.tick();
  if (system_tick.read_ms() >= 1ms)
    {
      static_event.dispatch();
      system_tick.reset();
    }
}