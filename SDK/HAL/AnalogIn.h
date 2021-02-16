#pragma once

#include <cstdint>

#include "SystemTick.h"
#include "macro.h"
#include "stm32f4xx_adc.h"
#include GEN_HEADER(TARGET_BASE, _adc)

extern StaticEvent system_events;

class AnalogIn
{
 private:
  ADCDriver _adc;
  uint16_t  _data;

 public:
  AnalogIn(PinName pin) : _adc(pin)
  {
    system_events.call([this] { process(); });
  }

  uint16_t read(void)
  {
    return _adc.read_u12();
  }

  operator uint16_t()
  {
    return _data;
  }

  void process()
  {
    _data = read();
  }
};
