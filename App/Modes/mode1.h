#pragma once

#include "mode.h"

void mode1()
{
  static Callback p;
  button[BtnLabel::Y].onPush([] {
    p = events.call({
        .event = [] {
          leds.toggle(LEDLabel::BTN_Y);
        },
        .cycle = 20,
        .interval = 50ms,
    });
  });
  button[BtnLabel::Y].onRelease([] {
    events.stop(p);
    events.call({[] { leds.write(LEDLabel::BTN_Y, Off); }});
  });

  button[BtnLabel::Z].onPush([] {
    events.call({[] { leds.write(LEDLabel::BTN_Z, On); }});
    events.stop(p);
    events.call({[] { leds.write(LEDLabel::BTN_Y, Off); }});
    modes.add(mode2);
  });
};
