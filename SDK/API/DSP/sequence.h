#pragma once

#include <cstdint>
#include <vector>

namespace bad
{
template <typename T>
class sequence
{
 public:
  struct Row
  {
    uint8_t step_rate;
    uint8_t playback_mode;
    uint8_t loop_start;
    uint8_t loop_end;
    uint8_t midi_channel;
  };
  struct Step
  {
    uint8_t note;
    uint8_t velocity;
    uint8_t gate;
    uint8_t chance;
    uint8_t offset;
    uint8_t tie;
  };

 private:
  std::vector<std::vector<T>> _sequence;

  uint8_t _cursor;
  uint8_t _cursor_max;

 public:
  sequence(uint8_t length, uint8_t variant = 1)
  {
    set_variant(variant);
    set_length(length);
    set_cursor(0);
  }

  void   set_variant() { _sequence.resize(variant); }
  size_t get_variant() { return _sequence.size(); }

  void set_length(uint8_t length)
  {
    for (auto &&i : _sequence)
      {
        i.resize(length);
        for (auto &&j : i) j = 0;
      }
  }

  T read(uint8_t variant = 0, uint8_t step = get_step()) { return _sequence[variant][step]; }

  void write(T value, uint8_t variant = 0, uint8_t step = get_step()) { _sequence[variant][step] = value; }

  T toggle(uint8_t variant = 0, uint8_t step = get_step()) { return _sequence[variant][step] = !_sequence[variant][step]; }

  void set_cursor(uint8_t cursor)
  {
    _cursor = cursor;
  }

  uint8_t get_step()
  {
    if (_cursor <= 0)
      return _cursor_max >> 1;
    else
      return _cursor >> 1;
  }

  void next()
  {
    if (_cursor_max <= _cursor)
      _cursor = 0U;
    else
      _cursor++;
  }

  void prev()
  {
    if (_cursor <= 0)
      _cursor = _cursor_max;
    else
      _cursor--;
  }
};
}  // namespace bad

bad::sequence<float> seq1(16);