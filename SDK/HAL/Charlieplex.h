#pragma once

#include <cstddef>
#include <cstdint>
#include <initializer_list>

#include "SystemTick.h"
#include "macro.h"
#include GEN_HEADER(TARGET_BASE, _gpio)
extern StaticEvent system_events;

enum LedState
{
  LED_OFF,
  LED_ON
};

class Charlieplex
{
 private:
  uint8_t _row_count = 0;
  uint8_t _column_count = 0;

  const uint32_t _row;
  const uint32_t _column;
  const uint32_t _total;

  PinName *  _pin;
  GPIO *     _gpio;
  uint8_t *  _buffer;
  uint32_t **_index;
  uint32_t **_lut;

 public:
  Charlieplex(std::initializer_list<PinName> pin)
      : _row(pin.size()),
        _column(_row - 1),
        _total(_row * _column),
        _pin(new PinName[_row]{}),
        _gpio(new GPIO[_row]{}),
        _buffer(new uint8_t[_row * (_row - 1)]{}),
        _index(new uint32_t *[_row] {}),
        _lut(new uint32_t *[_row] {})
  {
    std::copy(pin.begin(), pin.end(), _pin);

    for (size_t i = 0; i < _row; i++)
      {
        _index[i] = new uint32_t[_row - 1]{};
        _lut[i] = new uint32_t[_row - 1]{};
        _gpio[i] = GPIO().init(_pin[i]);
        _gpio[i].set_mode(GPIO::Mode::OUTPUT);
        for (uint32_t j = 0; j < _column; j++)
          {
            _index[i][j] = i * 4 + j;
            if (j >= i)
              {
                _lut[i][j] = j + 1;
              }
            else
              {
                _lut[i][j] = j;
              }
          }
      }
    // system_events.call([this] { process(); });
  }

  void write(size_t index, uint8_t state)
  {
    _buffer[index] = state;
  }

  void toggle(size_t index)
  {
    _buffer[index] = !_buffer[index];
  }

  // void brightness(uint8_t index, uint32_t brightness) {
  //     pwm_[index].write(brightness);
  // }

  uint8_t read(size_t index)
  {
    return _buffer[index];
  }

  void init()
  {
    for (uint32_t i = 0; i < _row; i++)
      {
        _gpio[i].set_mode(GPIO::Mode::INPUT);
      }
  }

  void process()
  {
    if (_column_count < _column - 1)
      {
        _column_count++;
      }
    else
      {
        _column_count = 0;
        if (_row_count < _row - 1)
          {
            _row_count++;
          }
        else
          {
            _row_count = 0;
          }
      }
    this->init();
    if (_buffer[_index[_row_count][_column_count]])
      {
        _gpio[_lut[_row_count][_column_count]].set_mode(GPIO::Mode::OUTPUT);
        _gpio[_lut[_row_count][_column_count]].write_output((uint32_t)GPIO::State::LOW);
        _gpio[_row_count].set_mode(GPIO::Mode::OUTPUT);
        _gpio[_row_count].write_output((uint32_t)GPIO::State::HIGH);
      }
  }
};
