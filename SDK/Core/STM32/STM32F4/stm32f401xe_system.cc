#ifdef STM32F401xE

#include "Literals.h"
#include "stm32f4xx.h"
#include "stm32f4xx_bus.h"
#include "stm32f4xx_pwr.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_system.h"

RTCControl SysClock;

__attribute__((weak)) void system_init()
{
  constexpr auto SystemCoreClock = 120MHz;
  constexpr auto Frequency = 1kHz;
  SysTick_Config(SystemCoreClock / Frequency);
}

__attribute__((weak)) void clock_init()
{
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
  // SysClock.SetAHBPrescaler(RTCControl::AHBPrescaler::DIV1);    // 120 MHz
  // SysClock.SetAPB1Prescaler(RTCControl::APB1Prescaler::DIV1);  // 120 MHz
  // SysClock.SetAPB2Prescaler(RTCControl::APB2Prescaler::DIV1);  // 120 MHz
}

#endif  // STM32F401xE