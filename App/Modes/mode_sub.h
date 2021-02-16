#pragma once

#include "BadBox.h"

void mode_sub()
{
  //----------------------------------------------------------------------------
  // Back to Normal
  //----------------------------------------------------------------------------
  button[BTN::SUB]
      .onRelease([] {
        for (size_t i = 0; i < BTN::STEP_NUM; i++)
          {
            leds.write((LED::i1 + i), seq[track_select].direct_read((i * 2) + substep));
          }
        substep = false;
        extern void mode_stop();
        modes.add(mode_stop);
      });

  //----------------------------------------------------------------------------
  // Sub Step
  //----------------------------------------------------------------------------
  for (size_t i = 0; i < (BTN::STEP_NUM + BTN::SUBSTEP_NUM); i++)
    {
      if ((i % 2) == 1)
        {
          button[((i / 2) + BTN::i1)]
              .onPush([i] {
                seq[track_select].toggle(i);
              });
        }
    }

  //----------------------------------------------------------------------------
  // Pattern Select
  //----------------------------------------------------------------------------
  for (size_t i = BTN::M; i < (BTN::M + BTN::INST_NUM); i++)
    {
      button[i]
          .onPush([i] {
            for (auto &&j : seq)
              {
                j.set_variant(i);
              }
            for (size_t j = 0; j < 5; j++)
              {
                leds.write((LED::M + j), OFF);
              }
            leds.write((LED::M + i), ON);
          });
    }
}