#pragma once

#include <cstdint>
#include <functional>

#include "SystemTick.h"
#include "common.h"
#include "macro.h"
#include GEN_HEADER(TARGET_BASE, _gpio)

extern StaticEvent system_events;

class UIButton
{
 private:
  volatile uint8_t button_buffer_ = 0;
  GPIO::Polarity   polarity_ = GPIO::Polarity::POSITIVE;
  GPIO::State      state_ = GPIO::State::LOW;
  GPIO             _gpio;

 public:
  UIButton(PinName        pin,
           GPIO::Pull     pull = GPIO::Pull::UP,
           GPIO::Polarity polarity = GPIO::Polarity::NEGATIVE) : _gpio()
  {
    _gpio.init(pin);
    _gpio.set_pull(pull);
    _gpio.set_mode(GPIO::Mode::INPUT);
    polarity_ = polarity;
    system_events.call([this] { process(); });
  }

  uint32_t read()
  {
    return _gpio.read_input() ^ (uint32_t)polarity_;
  }

  void process()
  {
    button_buffer_ = (button_buffer_ << 1) | read();
    switch (button_buffer_)
      {
        default:
          state_ = GPIO::State::LOW;  // stay released
          break;
        case 0b1111'1111:
          state_ = GPIO::State::HIGH;  // stay pressed
          break;
        case 0b1000'0000:
          state_ = GPIO::State::FALL;  // released
          break;
        case 0b0111'1111:
          state_ = GPIO::State::RISE;  // pressed
          break;
      }
  }

  bool is(GPIO::State state)
  {
    return state_ == state;
  }

  UIButton& onPush(Callback&& func)
  {
    if (state_ == GPIO::State::RISE)
      func();
    return *this;
  }
  UIButton& onRelease(Callback&& func)
  {
    if (state_ == GPIO::State::FALL)
      func();
    return *this;
  }
};