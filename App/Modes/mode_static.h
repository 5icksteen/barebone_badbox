#pragma once

#include "BadBox.h"

void mode_static()
{
  //----------------------------------------------------------------------------
  // SYNC Output
  //----------------------------------------------------------------------------
  if (seq[0].gate())
    {
      sync_out = 1;
      events.call({
          .event = [] { sync_out = 0; },
          .counter = 15ms,
      });
    }

  //----------------------------------------------------------------------------
  // Sample Gate
  //----------------------------------------------------------------------------
  for (size_t i = BTN::M; i < BTN::M + BTN::INST_NUM; i++)
    {
      if (seq[i].gate() && seq[i].read() && !seq[i].mute())
        {
          samplepack[i].gate();
          if (seq[i].get_run_status())
            {
              leds.toggle(LED::M + i);
              events.call({
                  .event = [i] { leds.toggle(LED::M + i); },
                  .counter = 50ms,
              });
            }
        }
    }

  //----------------------------------------------------------------------------
  // LED
  //----------------------------------------------------------------------------
  if (seq[track_select].get_run_status())
    {
      if (seq[track_select].get_rec_status())
        leds.write((LED::REC), ON);
      else
        leds.write((LED::REC), OFF);
      leds.write((LED::PLAY), ON);
      leds.write((LED::STOP), OFF);
    }
  else
    {
      leds.write((LED::REC), OFF);
      leds.write((LED::PLAY), OFF);
      leds.write((LED::STOP), ON);
    }

  for (size_t i = 0; i < 16; i++)
    {
      if ((i % 2) == substep)
        {
          if (seq[track_select].get_cursor() == i && seq[track_select].get_run_status())
            {
              if (seq[track_select].gate())
                {
                  leds.write(((i / 2) + 9), !seq[track_select].direct_read(i));
                  events.call({
                      .event = [i] {
                        leds.write(((i / 2) + 9), seq[track_select].direct_read(i));
                      },
                      .counter = 100ms,
                  });
                }
            }
          else
            {
              leds.write(((i / 2) + 9), seq[track_select].direct_read(i));
            }
        }
    }
}
