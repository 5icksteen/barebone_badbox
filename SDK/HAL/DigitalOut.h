#pragma once

#include <cstdint>

#include "macro.h"
#include GEN_HEADER(TARGET_BASE, _gpio)

class DigitalOut : public GPIO
{
 public:
  DigitalOut(PinName pin, std::uint32_t value = 0, Speed speed = Speed::VERY_HIGH)
  {
    GPIO::init(pin);
    set_speed(speed);
    set_mode(GPIO::Mode::OUTPUT);
    write(value);
  }

  void write(std::uint32_t value)
  {
    write_output(value);
  }

  void toggle()
  {
    toggle_output();
  }

  uint32_t read()
  {
    return read_output();
  }

  DigitalOut &operator=(std::uint32_t value)
  {
    write(value);
    return *this;
  }

  DigitalOut &operator=(DigitalOut &rhs);

  operator std::uint32_t()
  {
    return read();
  }
};