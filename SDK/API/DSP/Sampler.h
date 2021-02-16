#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

class Sampler
{
 private:
  const int16_t* _data;

  size_t  _sample_read;
  size_t  _sample_read_max;
  bool    _gate = false;
  int16_t _speed = 512;
  float   _volume = 0.5F;

 public:
  Sampler(const int16_t* data, size_t size)
  {
    _data = data;
    _sample_read = _sample_read_max = size << 8U;
  }

  inline Sampler& gate()
  {
    _gate = true;
    return *this;
  }

  inline Sampler& speed(int16_t speed = 512)
  {
    _speed = speed;
    return *this;
  }

  inline Sampler& volume(float volume = 0.0F)
  {
    _volume = volume;
    return *this;
  }

  inline int32_t playback()
  {
    if (_sample_read < _sample_read_max)
      _sample_read = _sample_read + _speed;
    else
      _sample_read = _sample_read_max;
    if (_gate == true)
      {
        _sample_read = 0U;
        _gate = false;
      }
    return _data[_sample_read >> 8U] * _volume;
  }
};
