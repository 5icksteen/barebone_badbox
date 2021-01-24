#include "Ticker.h"
Ticker ticker;

void SysTick_Handler()
{
  ticker.tick();
}