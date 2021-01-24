#pragma once

#include "Global.h"
#include "mode.h"

void mode1()
{
  static fp_t led_toggle = [] {
    led.toggle(LedType::BTN_Y);
  };
  Button[Key4].onPush([] {
    events.call({
        .event = led_toggle,
        .cycle = 20,
        .interval = 50ms,
    });
  });
  Button[Key4].onRelease([] {
    events.stop(led_toggle);
    events.call({[] { led.write(LedType::BTN_Y, Off); }});
  });

  Button[Key5].onPush([] {
    events.call({[] { led.write(LedType::BTN_Z, On); }});
    events.stop(led_toggle);
    events.call({[] { led.write(LedType::BTN_Y, Off); }});
    modes.add(mode2);
  });
  Button[Key5].onRelease([] {});
};

