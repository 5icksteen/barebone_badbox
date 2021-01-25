#pragma once

#include <cstdint>

#include "SystemTick.h"
#include "common.h"
#include "target.h"
extern StaticEvent system_events;

class UIButton : public GPIO
{
 private:
  volatile uint8_t button_buffer_;
  Polarity polarity_;
  State state_;

 public:
  UIButton(PinName pin, Pull pull = Pull::UP, Polarity polarity = Polarity::NEGATIVE)
  {
    GPIO::init(pin);
    set_pull(pull);
    set_mode(Mode::INPUT);
    polarity_ = polarity;
    system_events.call([this] { scan(); });
  }

  uint32_t read()
  {
    return read_input() ^ (uint32_t)polarity_;
  }

  void scan()
  {
    button_buffer_ = (button_buffer_ << 1) | read();
    switch (button_buffer_)
      {
        default:
          state_ = State::LOW;  // stay released
          break;
        case 0b1111'1111:
          state_ = State::HIGH;  // stay pressed
          break;
        case 0b1000'0000:
          state_ = State::FALL;  // released
          break;
        case 0b0111'1111:
          state_ = State::RISE;  // pressed
          break;
      }
  }

  bool is(State state)
  {
    return state_ == state;
  }

  void onPush(Callback &&func)
  {
    if (state_ == State::RISE)
      func();
  }
  void onRelease(Callback &&func)
  {
    if (state_ == State::FALL)
      func();
  }
};