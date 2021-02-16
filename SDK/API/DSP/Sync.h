// #pragma once

// #include <cstdint>

// #include "bpm.h"

// enum SyncType
// {
//   SYNC_1PPQN = 1,
//   SYNC_2PPQN = 2,
//   SYNC_4PPQN = 4,
//   SYNC_12PPQN = 12,
//   SYNC_24PPQN = 24,
//   SYNC_48PPQN = 48,
//   SYNC_96PPQN = 96,
//   SYNC_KORG = SYNC_2PPQN,
//   SYNC_TE = SYNC_2PPQN,
//   SYNC_MIDI = SYNC_24PPQN,
//   SYNC_DIN24 = SYNC_24PPQN,
//   SYNC_DIN_ROLAND = SYNC_24PPQN,
//   SYNC_DIN48 = SYNC_48PPQN,
//   SYNC_DIN_KORG = SYNC_48PPQN,
// };

// class SYNC
// {
//   static constexpr auto SYNC_PULSE = 15ms;

//   float _threashold;
//   bool  _prev_state;
//   bool  _current_state;

//   bool    _polarity;
//   uint8_t _buf;

//   uint16_t _sync_hold_off;

//   uint16_t _prev_time;

//   float _sync_midi_divider;

//   bool     _clock_tick;
//   uint16_t _clock_tick_interval;
//   uint16_t _clock_tick_counter;

//   bool  _midi_clock_tick;
//   float _midi_clock_tick_interval;

//  public:
//   bool read_clock()
//   {
//     bool tmp = _midi_clock_tick;
//     _midi_clock_tick = false;
//     return tmp;
//   }
//   void process()
//   {
//     if (_clock_tick)
//       {
//         _clock_tick_interval = read() - _prev_time;
//         _midi_clock_tick_interval = _clock_tick_interval * _sync_midi_divider;
//         _clock_tick_counter = 0;
//       }

//     if (_midi_clock_tick_interval < _clock_tick_counter)
//       {
//         _midi_clock_tick = true;
//         _midi_clock_tick_interval += _midi_clock_tick_interval;
//       }
//     else
//       {
//         _midi_clock_tick = false;
//       }

//     __SSAT(_clock_tick_counter++, 16);
//   }
// };