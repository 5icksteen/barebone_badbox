#pragma once

#include <stdint.h>

class Oscillator
{
 private:
  float sample_frequency_s_;
  float saw_voltage_;

 public:
  Oscillator(float freq_s)
  {
    sample_frequency_s_ = freq_s;
    saw_voltage_ = 0.5F;
  }
  ~Oscillator() {}

  inline float sawtooth(float frequency_hz, uint32_t reset_pulse)  //frew,triger,shuuki,detune
  {
    if (saw_voltage_ >= 0.5F || reset_pulse == 1U)
      {
        saw_voltage_ = -0.5F;
      }
    else
      {
        saw_voltage_ += frequency_hz * sample_frequency_s_;
      }
    return (saw_voltage_);
  }

  inline float triangle(float frequency_hz, uint32_t reset_pulse)  //frew,triger,shuuki,detune
  {
    float buf;
    buf = sawtooth(frequency_hz, reset_pulse) * 2U;
    if (buf >= 0.0F)
      {
        buf = 0.0F - buf;
      }
    return (buf + 0.5F);
  }

  inline float square(float frequency_hz, uint32_t reset_pulse)  //frew,triger,shuuki,detune
  {
    float buf;
    buf = sawtooth(frequency_hz, reset_pulse);
    if (buf >= 0.0F)
      {
        buf = 0.5F;
      }
    else
      {
        buf = -0.5F;
      }
    return (buf);
  }

  inline void reset()
  {
    saw_voltage_ = 0.5F;
  }
};
