#pragma once

#include <cstdint>

#include "target.h"

class Potentiometer
{
 private:
  bool running;
  uint8_t _adc_number;

  volatile uint32_t *datareg;

 public:
  Potentiometer(PinName pin) {}
  uint16_t read_u12(void) {}
  uint16_t read_u16(void) {}
  uint16_t read(void) {}
  operator auto() {}
};
