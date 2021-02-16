#ifdef STM32F411xE

#include "frequency.h"
#include "stm32f4xx.h"

__attribute__((weak)) void system_init()
{
  constexpr auto SystemClock = 16MHz;
  constexpr auto Frequency = 1kHz;
  SysTick_Config(SystemClock / Frequency);
}

#endif  // STM32F411xE