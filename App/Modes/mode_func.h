#pragma once

#include "BadBox.h"

void mode_func()
{
  //----------------------------------------------------------------------------
  // Knob
  //----------------------------------------------------------------------------
  knob[Knob::MASTER_TEMPO]
      .onChange([] {
        leds.write(LED::A, ON);
        events.call({
            .event = [] { leds.write(LED::A, OFF); },
            .counter = 200ms,
        });
        for (auto &&i : seq)
          {
            i.set_tempo((1.0F - knob[Knob::MASTER_TEMPO]) * 256);
          }
      });
  knob[Knob::MASTER_VOLUME]
      .onChange([] {
        leds.write(LED::D, ON);
        events.call({
            .event = [] { leds.write(LED::D, OFF); },
            .counter = 200ms,
        });
      });

  //----------------------------------------------------------------------------
  // Back to Normal
  //----------------------------------------------------------------------------
  button[BTN::FUNC]
      .onRelease([] {
        knob[Knob::MASTER_TEMPO].lock();
        knob[Knob::MASTER_VOLUME].lock();
        leds.write(LED::A, OFF);
        leds.write(LED::D, OFF);
        for (size_t i = BTN::M; i < (BTN::M + BTN::INST_NUM); i++)
          {
            leds.write((LED::M + i), 0);
          }
        if (seq[track_select].get_run_status())
          leds.write((LED::M + track_select), ON);
        extern void mode_stop();
        modes.add(mode_stop);
      });

  //----------------------------------------------------------------------------
  // Function
  //----------------------------------------------------------------------------
  button[BTN::REC]
      .onPush([] {
        if (seq[track_select].get_run_status())
          seq[track_select].set_rec_status(!seq[track_select].get_rec_status());
      });
  button[BTN::PLAY]
      .onPush([] {
        for (size_t i = BTN::M; i < (BTN::M + BTN::INST_NUM); i++)
          {
            seq[i].reset();
            seq[i].start();
          }
      });
  button[BTN::STOP]
      .onPush([] {
        for (size_t i = BTN::M; i < (BTN::M + BTN::INST_NUM); i++)
          {
            seq[i].stop();
          }
      });
  button[BTN::CLEAR]
      .onPush([] {
        for (size_t i = 0; i < (BTN::STEP_NUM + BTN::SUBSTEP_NUM); i++)
          {
            seq[track_select].direct_write(i, 0);
          }
      });

  //----------------------------------------------------------------------------
  // Mute
  //----------------------------------------------------------------------------
  for (size_t i = BTN::M; i < (BTN::M + BTN::INST_NUM); i++) // Mute
    {
      button[i].onPush([i] {
        seq[i].mute(!seq[i].mute());
        leds.write((LED::M + i), !seq[i].mute());
      });
    }
}
