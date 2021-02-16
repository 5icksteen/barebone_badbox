#pragma once

#include "Charlieplex.h"
#include "UIButton.h"
#include "macro.h"
#include GEN_HEADER(TARGET, )

namespace BTN
{
enum
{
  M,
  N,
  X,
  Y,
  Z,
  i1,
  i2,
  i3,
  i4,
  i5,
  i6,
  i7,
  i8,
  SUB,
  FUNC,
  NUM,
  INST_NUM = 5,
  STEP_NUM = 8,
  SUBSTEP_NUM = 8,
  // Alias Name
  C4 = i1,
  C4S = M,
  D4 = i2,
  D4S = N,
  E4 = i3,
  F4 = i4,
  F4S = X,
  G4 = i5,
  G4S = Y,
  A4 = i6,
  A4S = Z,
  B4 = i7,
  C5 = i8,

  REC = i1,
  PLAY = i2,
  STOP = i3,
  EDIT = i4,
  SAVE = i5,
  CLEAR = i6,
  CHAIN = i7,
  SYNC = i8,
  SIZE = NUM,
};
}

std::array button = {
    UIButton(PB4),                                               // BTN_M
    UIButton(PB3),                                               // BTN_N
    UIButton(PB10),                                              // BTN_X
    UIButton(PB13),                                              // BTN_Y
    UIButton(PB12),                                              // BTN_Z
    UIButton(PB6),                                               // BTN_1
    UIButton(PB5),                                               // BTN_2
    UIButton(PB7),                                               // BTN_3
    UIButton(PC15),                                              // BTN_4
    UIButton(PC14),                                              // BTN_5
    UIButton(PC13),                                              // BTN_6
    UIButton(PB9),                                               // BTN_7
    UIButton(PB8),                                               // BTN_8
    UIButton(PA15, GPIO::Pull::DOWN, GPIO::Polarity::POSITIVE),  // BTN_SUB
    UIButton(PB2),                                               // BTN_FUNC
};

Charlieplex leds = {
    PA10,
    PA8,
    PB15,
    PB14,
    PA9,
};
namespace LED
{
enum
{
  A,
  B,
  C,
  D,
  M,
  N,
  X,
  Y,
  Z,
  i1,
  i2,
  i3,
  i4,
  i5,
  i6,
  i7,
  i8,
  REC,
  PLAY,
  STOP,
  NUM,
  // Alias Name
  C4 = i1,
  C4S = M,
  D4 = i2,
  D4S = N,
  E4 = i3,
  F4 = i4,
  F4S = X,
  G4 = i5,
  G4S = Y,
  A4 = i6,
  A4S = Z,
  B4 = i7,
  C5 = i8,
};
}

#include "DigitalOut.h"
DigitalOut sync_out(PA1);

#include "AnalogIn.h"
#include "UIKnob.h"

std::array adc = {
    AnalogIn(PA2),
    AnalogIn(PA3),
    AnalogIn(PA4),
    AnalogIn(PB0),
};

namespace Knob
{
enum
{
  KICK_TUNE,
  SNARE_TUNE,
  HIHAT_TUNE,
  PARC_TUNE,
  SYM_TUNE,
  MASTER_TEMPO,
  KICK_VOLUME,
  SNARE_VOLUME,
  HIHAT_VOLUME,
  PARC_VOLUME,
  SYM_VOLUME,
  MASTER_VOLUME,
};
}

std::array knob = {
    UIKnob([] { return adc[0]; }),
    UIKnob([] { return adc[0]; }),
    UIKnob([] { return adc[0]; }),
    UIKnob([] { return adc[0]; }),
    UIKnob([] { return adc[0]; }),
    UIKnob([] { return adc[0]; }),
    UIKnob([] { return adc[3]; }),
    UIKnob([] { return adc[3]; }),
    UIKnob([] { return adc[3]; }),
    UIKnob([] { return adc[3]; }),
    UIKnob([] { return adc[3]; }),
    UIKnob([] { return adc[3]; }),
};

#include "PT8211.h"

PT8211 audio(PA6, PA5, PA7);

#include "BD808.h"
#include "CH808.h"
#include "OH808.h"
#include "RIM808.h"
#include "SD808.h"
#include "Sampler.h"

enum SampleIndex
{
  KICK,
  SNARE,
  HIHAT,
  PARC,
  SYM
};

std::array samplepack = {
    Sampler(BD808, countof(BD808)),
    Sampler(SD808, countof(SD808)),
    Sampler(CH808, countof(CH808)),
    Sampler(RIM808, countof(RIM808)),
    Sampler(OH808, countof(OH808)),
};

#include "Sequencer.h"

std::array seq = {
    Sequencer(16, 5),
    Sequencer(16, 5),
    Sequencer(16, 5),
    Sequencer(16, 5),
    Sequencer(16, 5),
};
enum DrumTriggerType
{
  kKick,
  kSnare,
  kClosedHihat,
  kRimShot,
  kOpenHihat,
  kDrumTriggerTypeNum,
};

#include "StaticAudioIRQ.h"
extern void    audio_process();
constexpr auto AUDIO_SAMPLE_FREQUENCY = 41.1kHz;
StaticAudioIRQ audio_irq(TIM3, audio_process, AUDIO_SAMPLE_FREQUENCY, 0);

#include "EventLoop.h"
EventLoop<128> events;

#include "FuncHolder.h"
extern void mode_stop();
FuncHolder  modes(mode_stop);

extern void mode_static();
FuncHolder  static_mode(mode_static);

bool    substep = false;
uint8_t track_select = 0;

#include "mode_func.h"
#include "mode_static.h"
#include "mode_stop.h"
#include "mode_sub.h"
