#pragma once

#include <array>
#include <cmath>
#include <cstdint>
#include <functional>
#include <utility>

#include "SystemTick.h"
#include "macro.h"
#include GEN_HEADER(TARGET_BASE, _adc)

extern StaticEvent system_events;

class UIKnob
{
 private:
  float _position = 0.5F;
  float _delta_position = 0.0F;
  float _hysteresis = 1.0F / 128.0F;
  bool  _status;
  bool  _lock = false;

  static constexpr float _divider = 1.0F / 4095.0F;

  std::function<uint16_t()> _func;

 public:
  UIKnob(std::function<uint16_t()>&& func) { _func = std::move(func); }

  float delta_position(float value) { return fabsf(_position - value); }
  void  set_hysteresis(float hysteresis) { _hysteresis = hysteresis; }

  operator float() { return read(); }

  float read() { return _position; }

  UIKnob& lock()
  {
    _lock = true;
    return *this;
  }

  UIKnob& unlock()
  {
    _lock = false;
    return *this;
  }

  UIKnob& onChange(Callback&& func = [] {})
  {
    float tmp = _func() * _divider;
    if (_lock)
      {
        if (delta_position(tmp) < _hysteresis)
          unlock();
      }
    else if (_hysteresis < delta_position(tmp))
      {
        _position = tmp;
        func();
      }
    return *this;
  }
};
