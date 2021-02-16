#pragma once

#include "BadBox.h"

void mode_stop()
{
  //----------------------------------------------------------------------------
  // Knob
  //----------------------------------------------------------------------------
  knob[track_select + Knob::KICK_TUNE].onChange([&] {
    leds.write(LED::A, ON);
    events.call({
        .event = [] { leds.write(LED::A, OFF); },
        .counter = 200ms,
    });
    samplepack[track_select].speed((1.0F - knob[track_select + Knob::KICK_TUNE]) * 1024.0F);
  });
  knob[track_select + Knob::KICK_VOLUME].onChange([&] {
    leds.write(LED::D, ON);
    events.call({
        .event = [] { leds.write(LED::D, OFF); },
        .counter = 200ms,
    });
    samplepack[track_select].volume(1.0F - knob[track_select + Knob::KICK_VOLUME]);
  });

  //----------------------------------------------------------------------------
  // Button
  //----------------------------------------------------------------------------
  button[BTN::FUNC]
      .onPush([] {
        for (size_t i = BTN::M; i < (BTN::M + BTN::INST_NUM); i++)
          {
            leds.write((LED::M + i), !seq[i].mute());
          }
        leds.write(LED::A, OFF);
        leds.write(LED::D, OFF);
        for (size_t i = 0; i < 5U; i++)
          {
            knob[i + Knob::KICK_TUNE].lock();
          }
        for (size_t i = 0; i < 5U; i++)
          {
            knob[i + Knob::KICK_VOLUME].lock();
          }

        extern void mode_func();
        modes.add(mode_func);
      });

  button[BTN::SUB]
      .onPush([] {
        substep = true;
        for (size_t i = 0; i < BTN::STEP_NUM; i++)
          {
            leds.write((LED::i1 + i), seq[track_select].direct_read((i * 2)) + substep);
          }
        extern void
        mode_sub();
        modes.add(mode_sub);
      });

  //----------------------------------------------------------------------------
  // Instrument Select
  //----------------------------------------------------------------------------
  for (size_t i = BTN::M; i < (BTN::M + BTN::INST_NUM); i++)
    {
      button[i]
          .onPush([i] {
            knob[track_select + Knob::KICK_TUNE].lock();
            knob[track_select + Knob::KICK_VOLUME].lock();
            track_select = i;
            if (seq[i].get_run_status() && !seq[i].get_rec_status())
              {
                for (size_t j = LED::M; j < LED::M + BTN::INST_NUM; j++)
                  {
                    leds.write(j, OFF);
                  }
                leds.write((LED::M + i), ON);
              }
            else
              {
                samplepack[i].gate();
                if (seq[i].get_rec_status())
                  seq[i].realtime_rec(1);
                leds.write((LED::M + i), ON);
                events.call({
                    .event = [i] { leds.write((LED::M + i), OFF); },
                    .counter = 50ms,
                });
              }
          });
    }

  //----------------------------------------------------------------------------
  // TR-REC
  //----------------------------------------------------------------------------
  for (size_t i = 0; i < (BTN::STEP_NUM + BTN::SUBSTEP_NUM); i++)
    {
      if ((i % 2) == 0)
        {
          button[((i / 2) + BTN::i1)]
              .onPush([i] {
                seq[track_select].toggle(i);
              });
        }
    }
};
