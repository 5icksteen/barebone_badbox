#pragma once

#include <cstdint>

#include "macro.h"
#include GEN_HEADER(TARGET_BASE, _gpio)
#include GEN_HEADER(TARGET_BASE, _spi)

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
    lrclk.set_speed(GPIO::Speed::VERY_HIGH);
    lrclk.set_mode(GPIO::Mode::OUTPUT);
  }

  void chanel_select(Channel ch) { lrclk.write_output((uint32_t)ch); }

  void transfer(auto ldata16, auto rdata16)
  {
    this->chanel_select(Channel::R);
    this->TransmitData16(rdata16);
    this->wait_for_transmition_complete();
    this->chanel_select(Channel::L);
    this->TransmitData16(ldata16);
  }

  void transfer(float ldataf, float rdataf)
  {
    int16_t ldata16 = __SSAT((ldataf)*INT16_MAX, 17);
    int16_t rdata16 = __SSAT((rdataf)*INT16_MAX, 17);
    this->chanel_select(Channel::R);
    this->TransmitData16(rdata16);
    this->wait_for_transmition_complete();
    this->chanel_select(Channel::L);
    this->TransmitData16(ldata16);
  }
};
