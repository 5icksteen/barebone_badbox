#pragma once

#include "mode.h"

void mode2()
{
  Button[BtnLabel::Y].onPush([] {
    events.call({[] { led.write(LEDLabel::BTN_X, On); }});
  });
  Button[BtnLabel::Y].onRelease([] {
    events.call({[] { led.write(LEDLabel::BTN_X, Off); }});
  });
  Button[BtnLabel::Z].onPush([] {
    events.call({[] { led.write(LEDLabel::BTN_Z, Off); }});
    events.call({[] { led.write(LEDLabel::BTN_X, Off); }});
    modes.add(mode1);
  });
};
