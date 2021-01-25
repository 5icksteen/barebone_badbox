#pragma once

#include <cstddef>
#include <cstdint>

#include "SystemTick.h"
// #include "softpwm.h"
#include "target.h"
extern StaticEvent system_events;

enum LedState
{
  LED_OFF,
  LED_ON
};

template <uint32_t row, uint32_t resolution>
class Charlieplex
{
 private:
  const uint32_t row_ = row;
  const uint32_t column_ = row - 1;
  const uint32_t total_ = row_ * column_;
  // const uint32_t resolution_ = resolution;

  uint8_t row_count_ = 0;
  uint8_t column_count_ = 0;

  GPIO gpio_[row];
  // SoftPwm  pwm_[row * (row - 1)];
  uint8_t buffer_[row * (row - 1)];
  uint32_t index_[row][row - 1];
  uint32_t lut_[row][row - 1];

 public:
  Charlieplex(const PinName* pin)
  {
    for (size_t i = 0; i < row_; i++)
      {
        gpio_[i] = GPIO().init(pin[i]);
        gpio_[i].set_mode(GPIO::Mode::OUTPUT);
        for (uint32_t j = 0; j < column_; j++)
          {
            // pwm_[i * j] = SoftPwm();
            // pwm_[i * j].init(pin[i]);
            // pwm_[i * j].write(resolution);
            index_[i][j] = i * 4 + j;
            if (j >= i)
              {
                lut_[i][j] = j + 1;
              }
            else
              {
                lut_[i][j] = j;
              }
          }
      }
    system_events.call([this] { scan(); });
  }

  void write(uint32_t index, uint8_t state)
  {
    buffer_[index] = state;
  }

  void toggle(uint32_t index)
  {
    buffer_[index] = !buffer_[index];
  }

  // void brightness(uint8_t index, uint32_t brightness) {
  //     pwm_[index].write(brightness);
  // }

  uint8_t read(uint8_t index)
  {
    return buffer_[index];
  }

  void init()
  {
    for (uint32_t i = 0; i < row_; i++)
      {
        gpio_[i].set_mode(GPIO::Mode::INPUT);
      }
  }

  void scan()
  {
    if (column_count_ < column_ - 1)
      {
        column_count_++;
      }
    else
      {
        column_count_ = 0;
        if (row_count_ < row_ - 1)
          {
            row_count_++;
          }
        else
          {
            row_count_ = 0;
          }
      }
    this->init();
    if (buffer_[index_[row_count_][column_count_]])
      {
        gpio_[lut_[row_count_][column_count_]].set_mode(GPIO::Mode::OUTPUT);
        gpio_[lut_[row_count_][column_count_]].write_output((uint32_t)GPIO::State::LOW);
        gpio_[row_count_].set_mode(GPIO::Mode::OUTPUT);
        gpio_[row_count_].write_output((uint32_t)GPIO::State::HIGH);
      }
  }
};
