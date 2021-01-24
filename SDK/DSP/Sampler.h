#pragma once

#include <stdint.h>

class Sampler
{
 private:
  const int16_t* data;
  uint32_t size;
  uint32_t sample_read;
  uint32_t sample_read_pointer;

 public:
  Sampler(const int16_t* sample_data, int32_t sample_size)
  {
    data = sample_data;
    size = sample_size;
    sample_read = 0U;
  }

  ~Sampler() {}

  int32_t play(uint8_t trigger, uint16_t speed)
  {
    if (sample_read < size << 8U) sample_read = sample_read + speed;
    if (sample_read > size << 8U) sample_read = size << 8U;
    if (trigger >= 1U) sample_read = 0U;
    sample_read_pointer = sample_read >> 8U;
    return data[sample_read_pointer];
  }
};
