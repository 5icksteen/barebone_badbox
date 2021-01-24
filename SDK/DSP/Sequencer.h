#pragma once

#include <stdint.h>

#include "Math_Util.h"

class Sequencer
{
 private:
  uint8_t* sequence;
  uint8_t pointer;
  uint8_t step_max;
  uint8_t step_length;

 public:
  Sequencer(uint8_t step)
  {
    sequence = new uint8_t[step]();
    step_max = step;
    step_length = step_max;
    pointer = 0U;
  }

  ~Sequencer() { delete[] sequence; }

  uint8_t read()
  {
    return sequence[pointer];
  }

  uint8_t read(uint8_t step)
  {
    return sequence[step];
  }

  void write(uint8_t value)
  {
    sequence[pointer] = value;
  }

  void write(uint8_t value, uint8_t step)
  {
    sequence[step] = value;
  }

  void next()
  {
    if (step_length - 1u > pointer)
      {
        pointer++;
      }
    else
      {
        pointer = 0U;
      }
  }

  void prev()
  {
    pointer--;
  }

  void reset()
  {
    pointer = 0U;
  }

  void set_step_length(int8_t value)
  {
    step_length = limit(value, 0, step_max);
  }

  void set_pointer(uint8_t value)
  {
    pointer = value;
  }

  uint8_t get_pointer()
  {
    return pointer;
  }
};
