#pragma once

#include "Global.h"
#include "mode.h"

void mode2()
{
  Button[Key4].onPush([] {
    events.call({[] { led.write(LedType::BTN_X, On); }});
  });
  Button[Key4].onRelease([] {
    events.call({[] { led.write(LedType::BTN_X, Off); }});
  });
  Button[Key5].onPush([] {
    events.call({[] { led.write(LedType::BTN_Z, Off); }});
    events.call({[] { led.write(LedType::BTN_X, Off); }});
    modes.add(mode1);
  });
  Button[Key5].onRelease([] {});
};
