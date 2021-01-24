#pragma once

#include "UIButton.h"
#include "Charlieplex.h"
#include "EventLoop.h"
#include "Led.h"
#include "Macro.h"
#include "target.h"

enum BtnName
{
  Key1,
  Key2,
  Key3,
  Key4,
  Key5,
};
UIButton Button[] = {
    UIButton(PB4),
    UIButton(PB3),
    UIButton(PB10),
    UIButton(PB13),
    UIButton(PB12),
};

EventLoop events;

constexpr PinName charlieplex_pin[] = {
    PA10,
    PA8,
    PB15,
    PB14,
    PA9,
};
Charlieplex<countof(charlieplex_pin), 4> led(charlieplex_pin);
enum LedType
{
  POT_1,
  POT_2,
  POT_3,
  POT_4,
  BTN_M,
  BTN_N,
  BTN_X,
  BTN_Y,
  BTN_Z,
  BTN_1,
  BTN_2,
  BTN_3,
  BTN_4,
  BTN_5,
  BTN_6,
  BTN_7,
  BTN_8,
  LED_NUM,
};
