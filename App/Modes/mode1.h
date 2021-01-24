#pragma once

#include "mode.h"

void mode1()
{
  static Callback p;
  Button[BtnLabel::Y].onPush([] {
    p = events.call({
        .event = [] {
          led.toggle(LEDLabel::BTN_Y);
        },
        .cycle = 20,
        .interval = 50ms,
    });
  });
  Button[BtnLabel::Y].onRelease([] {
    events.stop(p);
    events.call({[] { led.write(LEDLabel::BTN_Y, Off); }});
  });

  Button[BtnLabel::Z].onPush([] {
    events.call({[] { led.write(LEDLabel::BTN_Z, On); }});
    events.stop(p);
    events.call({[] { led.write(LEDLabel::BTN_Y, Off); }});
    modes.add(mode2);
  });
};
