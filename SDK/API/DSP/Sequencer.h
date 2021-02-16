#pragma once

#include <cstdint>

#include "Tempo.h"

extern StaticEvent system_events;
Tempo              _master_tempo;

class Sequencer
{
 private:
  std::vector<std::vector<uint8_t>> _sequence;

  uint8_t  _cursor = 0;
  uint16_t _count = 0;
  uint16_t _length = 6;
  uint16_t _half_length = 3;
  bool     _gate = false;
  bool     _half_gate = false;
  bool     _run_status = false;
  bool     _rec_status = false;
  bool     _mute = false;
  uint8_t  _variant = 0;

 public:
  Sequencer(uint8_t step_length, uint8_t variant_length = 1)
  {
    set_variant_length(variant_length);
    set_step_length(step_length);
    set_cursor(0);
    system_events.call([this] { process(); });
  }

  uint8_t read() { return _sequence[_variant][_cursor]; }
  uint8_t direct_read(uint8_t step) { return _sequence[_variant][step]; }

  void write(uint8_t value) { _sequence[_variant][_cursor] = value; }
  void direct_write(uint8_t step, uint8_t value) { _sequence[_variant][step] = value; }

  uint8_t toggle(uint8_t step) { return _sequence[_variant][step] = !_sequence[_variant][step]; }

  void next()
  {
    if (_sequence[_variant].size() - 1u > _cursor)
      {
        _cursor++;
      }
    else
      {
        _cursor = 0U;
      }
  }

  void prev()
  {
    _cursor--;
  }

  void start()
  {
    _master_tempo.start();
    _gate = true;
    _run_status = true;
  }
  void stop()
  {
    _master_tempo.stop();
    _run_status = false;
  }

  void reset()
  {
    _cursor = 0U;
    _count = 0;
    _master_tempo.reset();
  }

  void    set_cursor(uint8_t cursor) { _cursor = cursor; }
  uint8_t get_cursor() { return _cursor; }
  void    set_variant(uint8_t variant) { _variant = variant; }
  uint8_t get_variant() { return _variant; }

  void   set_variant_length(uint8_t variant) { _sequence.resize(variant); }
  size_t get_variant_length() { return _sequence.size(); }

  void set_step_length(int8_t step_length)
  {
    for (auto &&i : _sequence)
      {
        i.resize(step_length);
        for (auto &&j : i) j = 0;
      }
  }

  void set_tempo(float bpm) { _master_tempo.set(bpm); }

  void set_length(float value)
  {
    _length = _master_tempo.get_timebase() * value / 4;
  }

  bool gate() { return _gate; }

  bool get_run_status() { return _run_status; }
  bool get_rec_status() { return _rec_status; }
  void set_rec_status(bool rec_status) { _rec_status = rec_status; }

  void mute(bool set) { _mute = set; }
  bool mute() { return _mute; }

  void process()
  {
    if (_master_tempo.clock()) _count++;
    if (_length <= _count)
      {
        next();
        _gate = true;
        _count = 0;
      }
    else
      {
        _gate = false;
      }
    if (_half_length <= _count)
      {
        _half_gate = true;
      }
    else
      {
        _half_gate = false;
      }
  }

  void realtime_rec(uint8_t value)
  {
    if (_half_gate = true)
      _sequence[_variant][_cursor] = value;
    else
      {
        if (_sequence[_variant].size() - 1u > _cursor)
          {
            _sequence[_variant][_cursor + 1] = value;
          }
        else
          {
            _sequence[_variant][0] = value;
          }
      }
  }
};

// using note = float;
// consteval note operator""note(long double value)
// {
//   return note(value / 4);
// }

// auto beat = 4note;
// enum Beat
// {
//   n32 = 3,
//   n16 = 6,
//   n16_ = 9,
//   n8 = 12,
//   n8_ = 16,
//   n4 = 24,
//   n4_ = 36,
//   n2 = 48,
//   n1 = 96
// };
