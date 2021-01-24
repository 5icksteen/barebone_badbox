#pragma once

#ifdef STM32F4

#include <cstdint>

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"

class ADConverter : public GPIO
{
 public:
  ADConverter(PinName pin) { GPIO::init(pin); }
};

#endif  // STM32F4