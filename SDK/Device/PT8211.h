#pragma once

#include <cstdint>

#include "stm32f4xx_gpio.h"
#include "stm32f4xx_spi.h"
#include "target.h"

class PT8211 : public SPI
{
  enum class Channel
  {
    R,
    L
  };
  GPIO lrclk;

 public:
  PT8211(PinName ws, PinName bck, PinName din) : SPI(din, NC, bck)
  {
    lrclk.init(ws);
  }

  void chanel_select(Channel ch) { lrclk.write_output((uint32_t)ch); }

  void transfer(uint16_t ldata, uint16_t rdata)
  {
    this->chanel_select(Channel::R);
    this->TransmitData16(rdata);
    this->wait_for_transmition_complete();
    this->chanel_select(Channel::L);
    this->TransmitData16(ldata);
  }
};
