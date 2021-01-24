#pragma once

#include <cstdint>

#include "target.h"

class AnalogIn : public ADConverter
{
 private:
  bool running;
  uint8_t _adc_number;
  volatile uint32_t *datareg;

 public:
  AnalogIn(PinName pin) : ADConverter(pin)
  {
  }

  uint16_t read_u12(void)
  {
    // ADC1->SQR3 = _adc_number << ADC_SQR3_SQ1_Pos;  // Select ADC Channel
    // ADC1->CR2 |= ADC_CR2_SWSTART;                  // Start Conversion
    // while (!(ADC1->SR & ADC_SR_EOC)) continue;     // Check EOC Flag
    // return ADC1->DR & ADC_DR_DATA;
  }

  uint16_t read_u16(void)
  {
    // auto value = read_u12();
    // return (value << 4 & (uint16_t)0xFFF0) |
    //        (value >> 8 & (uint16_t)0x000F);
  }

  uint16_t read(void)
  {
    // return read_u12() / (float)0xFFF;
  }

  operator auto()
  {
    // return read();
  }
};
