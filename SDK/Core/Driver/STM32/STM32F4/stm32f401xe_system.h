#pragma once

#ifdef STM32F401xE

#include "frequency.h"
#include "macro.h"
#include "nvic.h"
#include GEN_HEADER(TARGET, )
#include GEN_HEADER(TARGET_BASE, _bus)
#include GEN_HEADER(TARGET_BASE, _pwr)
#include GEN_HEADER(TARGET_BASE, _rcc)
#include GEN_HEADER(TARGET_BASE, _system)

RTCControl SysClock;

__attribute__((weak)) void system_preinit()
{
  SCB->VTOR = (uint32_t)ROM_START;
  NVIC_CopyVector();
  __Enable_FPU();
}

__attribute__((weak)) void system_init()
{
  constexpr auto SystemCoreClock = 120MHz;
  constexpr auto Frequency = 1kHz;
  SysTick_Config(SystemCoreClock / Frequency);

  APB1_GRP1_EnableClock(RCC_APB1ENR_PWREN);
  PWR_SetRegulVoltageScaling(RegulatorVoltage::SCALE2);

  FLASH_SetLatency(FlashLatency::_3WS);

  SysClock.HSE_Enable();

  // Setup PLL
  SysClock.SetPLLSource(RTCControl::PLLSource::HSE);  // External 8 MHz xtal on OSC_IN/OSC_OUT
  SysClock.SetPLLM(8);                                // VCO input clock = 1 MHz (8 MHz / 8)
  SysClock.SetPLLN(240);                              // VCO output clock = 240 MHz (1 MHz * 240)
  SysClock.PLL_Enable();

  // Setup Bus
  SysClock.SetSysClkSource(RTCControl::SysClockSource::PLL);
  SysClock.SetAHBPrescaler(RTCControl::AHBPrescaler::DIV1);    // 120 MHz
  SysClock.SetAPB1Prescaler(RTCControl::APB1Prescaler::DIV2);  // 60 MHz
  SysClock.SetAPB2Prescaler(RTCControl::APB2Prescaler::DIV1);  // 120 MHz

  NVIC_EnableIRQ(SysTick_IRQn);
  NVIC_SetPriority(SysTick_IRQn, 0);
  NVIC_EnableIRQ(PendSV_IRQn);
  NVIC_SetPriority(PendSV_IRQn, 90);
}

#endif  // STM32F401xE