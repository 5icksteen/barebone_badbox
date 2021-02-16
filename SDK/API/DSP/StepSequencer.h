#pragma once

#include <cstdint>
#include <vector>

#include "Tempo.h"
#include "sequence.h"

extern StaticEvent system_events;
Tempo              _master_tempo;

namespace bad
{
class StepSequencer
{
 private:
  std::vector<sequence<float>> _sequence;

  uint8_t  _pointer = 0;
  uint16_t _count = 0;
  uint16_t _length = 6;
  bool     _gate = false;
  bool     _half_gate = false;
  bool     _run_status = false;
  bool     _rec_status = false;
  bool     _mute = false;

 public:
  StepSequencer(uint8_t track, uint8_t step)
  {
    _sequence.resize(track);
    for (auto &&i : _sequence) i.set_step_length(step);
    system_events.call([this] { process(); });
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
    _master_tempo.reset();
    for (auto &&i : _sequence) i.set_cursor(0);
    _count = 0;
  }

  void process()
  {
    if (_master_tempo.clock()) _count++;
    if (_length <= _count)
      {
        _gate = true;
        _count = 0;
        for (auto &&i : _sequence) i.next();
      }
    else
      {
        _gate = false;
      }
  }

  bool gate() { return _gate; }
};
}  // namespace bad
