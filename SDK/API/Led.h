#pragma once

#include <cstdint>

#include "target.h"

class LED : public GPIO
{
  enum class Polarity
  {
    POSITIVE,
    NEGATIVE
  };
  LED::Polarity polarity_;

 public:
  LED(PinName pin,
      bool value = 0,
      LED::Polarity polarity = LED::Polarity::POSITIVE,
      Speed speed = Speed::VERY_HIGH)
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

  LED& operator=(LED& rhs)
  {
    __disable_irq();
    write(rhs.read());
    __enable_irq();
    return *this;
  }

  LED& operator=(bool value)
  {
    write(value);
    return *this;
  }

  operator bool()
  {
    return read();
  }
};