#pragma once

#include "mode.h"

void mode2()
{
  button[BtnLabel::Y].onPush([] {
    events.call({[] { leds.write(LEDLabel::BTN_X, On); }});
  });
  button[BtnLabel::Y].onRelease([] {
    events.call({[] { leds.write(LEDLabel::BTN_X, Off); }});
  });
  button[BtnLabel::Z].onPush([] {
    events.call({[] { leds.write(LEDLabel::BTN_Z, Off); }});
    events.call({[] { leds.write(LEDLabel::BTN_X, Off); }});
    modes.add(mode1);
  });
};
