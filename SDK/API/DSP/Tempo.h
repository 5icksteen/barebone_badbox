#pragma once

#include <cstdint>

#include "SystemTick.h"
#include "second.h"

extern StaticEvent system_events;

class Tempo
{
 private:
  static constexpr uint16_t ONE_MINUTE = 60000ms;

  SystemTimer timer;

  float    _bpm = 120;
  bool     _clock = false;
  uint16_t _timebase = 24;
  float    _msec_per_timebase = ONE_MINUTE / _timebase;

 public:
  Tempo()
  {
    system_events.call([this] { process(); });
  }
  void set(float bpm)
  {
    _bpm = bpm;
  }
  void set_timebase(uint16_t timebase)
  {
    _timebase = timebase;
    _msec_per_timebase = ONE_MINUTE / timebase;
  }
  uint16_t get_timebase()
  {
    return _timebase;
  }
  void process()
  {
    auto time_now = timer.read();
    if ((_msec_per_timebase / _bpm) <= time_now)
      {
        _clock = true;
        timer.reset();
      }
    else
      _clock = false;
  }

  bool clock() { return _clock; }

  void start() { timer.start(); }
  void stop() { timer.stop(); }
  void reset() { timer.reset(); }
};