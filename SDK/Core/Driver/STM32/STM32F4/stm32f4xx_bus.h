#pragma once

#ifdef STM32F4

#include "stm32f4xx.h"

__STATIC_INLINE void AHB1_GRP1_EnableClock(uint32_t Periphs)
{
  SET_BIT(RCC->AHB1ENR, Periphs);
  RCC->AHB1ENR;
}

__STATIC_INLINE uint32_t AHB1_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return (READ_BIT(RCC->AHB1ENR, Periphs) == Periphs);
}

__STATIC_INLINE void AHB1_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB1ENR, Periphs);
}

__STATIC_INLINE void AHB1_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->AHB1RSTR, Periphs);
}

__STATIC_INLINE void AHB1_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB1RSTR, Periphs);
}

__STATIC_INLINE void AHB1_GRP1_EnableClockLowPower(uint32_t Periphs)
{
  SET_BIT(RCC->AHB1LPENR, Periphs);
  RCC->AHB1LPENR;
}

__STATIC_INLINE void AHB1_GRP1_DisableClockLowPower(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB1LPENR, Periphs);
}

__STATIC_INLINE void AHB2_GRP1_EnableClock(uint32_t Periphs)
{
  SET_BIT(RCC->AHB2ENR, Periphs);
  RCC->AHB2ENR;
}

__STATIC_INLINE uint32_t AHB2_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return (READ_BIT(RCC->AHB2ENR, Periphs) == Periphs);
}

__STATIC_INLINE void AHB2_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB2ENR, Periphs);
}

__STATIC_INLINE void AHB2_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->AHB2RSTR, Periphs);
}

__STATIC_INLINE void AHB2_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB2RSTR, Periphs);
}

__STATIC_INLINE void AHB2_GRP1_EnableClockLowPower(uint32_t Periphs)
{
  SET_BIT(RCC->AHB2LPENR, Periphs);
  RCC->AHB2LPENR;
}

__STATIC_INLINE void AHB2_GRP1_DisableClockLowPower(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB2LPENR, Periphs);
}

__STATIC_INLINE void AHB3_GRP1_EnableClock(uint32_t Periphs)
{
  SET_BIT(RCC->AHB3ENR, Periphs);
  RCC->AHB3ENR;
}

__STATIC_INLINE uint32_t AHB3_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return (READ_BIT(RCC->AHB3ENR, Periphs) == Periphs);
}

__STATIC_INLINE void AHB3_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB3ENR, Periphs);
}

__STATIC_INLINE void AHB3_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->AHB3RSTR, Periphs);
}

__STATIC_INLINE void AHB3_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB3RSTR, Periphs);
}

__STATIC_INLINE void AHB3_GRP1_EnableClockLowPower(uint32_t Periphs)
{
  SET_BIT(RCC->AHB3LPENR, Periphs);
  RCC->AHB3LPENR;
}

__STATIC_INLINE void AHB3_GRP1_DisableClockLowPower(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB3LPENR, Periphs);
}

__STATIC_INLINE void APB1_GRP1_EnableClock(uint32_t Periphs)
{
  SET_BIT(RCC->APB1ENR, Periphs);
  RCC->APB1ENR;
}

__STATIC_INLINE uint32_t APB1_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return (READ_BIT(RCC->APB1ENR, Periphs) == Periphs);
}

__STATIC_INLINE void APB1_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1ENR, Periphs);
}

__STATIC_INLINE void APB1_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->APB1RSTR, Periphs);
}

__STATIC_INLINE void APB1_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1RSTR, Periphs);
}

__STATIC_INLINE void APB1_GRP1_EnableClockLowPower(uint32_t Periphs)
{
  SET_BIT(RCC->APB1LPENR, Periphs);
  RCC->APB1LPENR;
}

__STATIC_INLINE void APB1_GRP1_DisableClockLowPower(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1LPENR, Periphs);
}

__STATIC_INLINE void APB2_GRP1_EnableClock(uint32_t Periphs)
{
  SET_BIT(RCC->APB2ENR, Periphs);
  RCC->APB2ENR;
}

__STATIC_INLINE uint32_t APB2_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return (READ_BIT(RCC->APB2ENR, Periphs) == Periphs);
}

__STATIC_INLINE void APB2_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB2ENR, Periphs);
}

__STATIC_INLINE void APB2_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->APB2RSTR, Periphs);
}

__STATIC_INLINE void APB2_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB2RSTR, Periphs);
}

__STATIC_INLINE void APB2_GRP1_EnableClockLowPower(uint32_t Periphs)
{
  SET_BIT(RCC->APB2LPENR, Periphs);
  RCC->APB2LPENR;
}

__STATIC_INLINE void APB2_GRP1_DisableClockLowPower(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB2LPENR, Periphs);
}

#endif  // STM32F4