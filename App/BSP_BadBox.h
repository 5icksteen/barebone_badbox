#pragma once

#include "Charlieplex.h"
#include "Macro.h"
#include "UIButton.h"
#include "target.h"

enum BtnLabel
{
  M,
  N,
  X,
  Y,
  Z,
  STEP1,
  STEP2,
  STEP3,
  STEP4,
  STEP5,
  STEP6,
  STEP7,
  STEP8,
  BTN_NUM,
};
UIButton button[] = {
    UIButton(PB4),
    UIButton(PB3),
    UIButton(PB10),
    UIButton(PB13),
    UIButton(PB12),
};

constexpr PinName charlieplex_pin[] = {
    PA10,
    PA8,
    PB15,
    PB14,
    PA9,
};
Charlieplex<countof(charlieplex_pin), 4> leds(charlieplex_pin);
enum LEDLabel
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
