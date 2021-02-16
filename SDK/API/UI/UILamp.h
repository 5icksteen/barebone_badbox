#pragma once

#include <cstdint>

#include "macro.h"
#include GEN_HEADER(TARGET_BASE, _gpio)

class UILamp : public GPIO
{
  enum class Polarity
  {
    POSITIVE,
    NEGATIVE
  };
  UILamp::Polarity polarity_;

 public:
  UILamp(PinName          pin,
         bool             value = 0,
         UILamp::Polarity polarity = UILamp::Polarity::POSITIVE,
         Speed            speed = Speed::VERY_HIGH)
  {
    GPIO::init(pin);
    polarity_ = polarity;
    set_speed(speed);
    set_mode(GPIO::Mode::OUTPUT);
    write(value);
  }

  void write(bool value) { write_output(value ^ (bool)polarity_); }

  void toggle() { toggle_output(); }

  bool read() { return read_output(); }

  UILamp& operator=(UILamp& rhs)
  {
    __disable_irq();
    write(rhs.read());
    __enable_irq();
    return *this;
  }

  UILamp& operator=(bool value)
  {
    write(value);
    return *this;
  }

  operator bool()
  {
    return read();
  }
};