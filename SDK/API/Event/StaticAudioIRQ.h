#pragma once

#include "macro.h"
#include GEN_HEADER(TARGET_BASE, _tim)

void StaticAudioIRQ_Handler();

class StaticAudioIRQ : public Timer
{
 public:
  StaticAudioIRQ(TIM_TypeDef *TIMx,
                 auto &&      callback,
                 uint32_t     freq_hz = 41100Hz,
                 uint32_t     priority = 0) : Timer(TIMx)
  {
    _callback = std::forward<decltype(callback)>(callback);
    EnableClock();
    SetAutoReload((120000000 / freq_hz) - 1);
    GenerateEvent_UPDATE();
    EnableIT_UPDATE();
    EnableCounter();
    SetPriority(priority);
    SetVector((uint32_t)StaticAudioIRQ_Handler);
    EnableIRQ();
  }
};

extern StaticAudioIRQ audio_irq;
extern Charlieplex    leds;

void StaticAudioIRQ_Handler()
{
  audio_irq.dispatch();
  leds.process();
}