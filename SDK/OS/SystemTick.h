#pragma once

#include "StaticEvent.h"
#include "Ticker.h"

Ticker system_tick;
StaticEvent system_events;

void SysTick_Handler()
{
  system_tick.tick();
  if (system_tick.read_ms() >= 1ms)
    {
      system_events.dispatch();
      system_tick.reset();
    }
}