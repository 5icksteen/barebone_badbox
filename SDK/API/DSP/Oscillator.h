#pragma once

#include <stdint.h>

class Oscillator
{
 private:
  float sample_frequency_s_;
  float _saw_voltage = 0.0F;
  float _frequency_hz;

 public:
  Oscillator(float freq_s)
  {
    sample_frequency_s_ = freq_s;
  }
  ~Oscillator() {}

  Oscillator& freq(float frequency_hz)
  {
    _frequency_hz = frequency_hz;
    return *this;
  }

  Oscillator& reset()
  {
    _saw_voltage = 0.0F;
    return *this;
  }

  float sawtooth()
  {
    _saw_voltage += _frequency_hz * sample_frequency_s_;
    if (1.0F <= _saw_voltage)
      {
        _saw_voltage = 0.0F;
      }
    return (_saw_voltage - 0.5F);
  }

  float triangle()
  {
    auto buf = sawtooth();
    if (0.0F <= buf)
      {
        return (buf - 0.25F) * 4;
      }
    else
      {
        return (-buf - 0.25F) * 4;
      }
  }

  float square()
  {
    auto  buf = sawtooth();
    float sq = 0.0F;
    if (0.0F <= buf)
      {
        sq = !sq;
      }
    return (sq - 0.5F) * 2;
  }
};
