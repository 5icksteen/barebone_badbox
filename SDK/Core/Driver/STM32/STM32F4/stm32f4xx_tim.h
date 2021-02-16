#pragma once

#include <utility>

#include "frequency.h"
#include "common.h"
#include "macro.h"
#include "nvic.h"
#include GEN_HEADER(TARGET,)

void StaticAudioIRQ_Handler();

class Timer
{
 protected:
  TIM_TypeDef *_TIMx;
  Callback     _callback = [] {};

 public:
  Timer(TIM_TypeDef *TIMx)
  {
    _TIMx = TIMx;
  }

  void call(auto &&callback, uint32_t freq_hz = 41100Hz, uint32_t priority = 0)
  {
    _callback = std::forward<decltype(callback)>(callback);
    EnableClock();
    SetAutoReload((120000000 / freq_hz) - 1);
    GenerateEvent_UPDATE();
    EnableIT_UPDATE();
    EnableCounter();
    NVIC_SetPriority(GetTIM_IRQn(), priority);
    NVIC_EnableIRQ(GetTIM_IRQn());
  }

  void dispatch()
  {
    if (IsActiveFlag_UPDATE())
      {
        ClearFlag_UPDATE();
        _callback();
      }
  }

  void SetPriority(uint32_t priority)
  {
    NVIC_SetPriority(GetTIM_IRQn(), priority);
  }

  void SetVector(uint32_t vector)
  {
    NVIC_SetVector(GetTIM_IRQn(), vector);
  }

  void EnableIRQ()
  {
    NVIC_EnableIRQ(GetTIM_IRQn());
  }

  IRQn_Type GetTIM_IRQn()
  {
    if (_TIMx == TIM1)
      {
        return TIM1_UP_TIM10_IRQn;
      }
    else if (_TIMx == TIM2)
      {
        return TIM2_IRQn;
      }
    else if (_TIMx == TIM3)
      {
        return TIM3_IRQn;
      }
    else if (_TIMx == TIM4)
      {
        return TIM4_IRQn;
      }
    else if (_TIMx == TIM5)
      {
        return TIM5_IRQn;
      }
    else if (_TIMx == TIM9)
      {
        return TIM1_BRK_TIM9_IRQn;
      }
    else if (_TIMx == TIM10)
      {
        return TIM1_UP_TIM10_IRQn;
      }
    else if (_TIMx == TIM11)
      {
        return TIM1_TRG_COM_TIM11_IRQn;
      }
  }

  void EnableClock()
  {
    if (_TIMx == TIM1)
      {
        APB2_GRP1_EnableClock(RCC_APB2ENR_TIM1EN);
      }
    else if (_TIMx == TIM2)
      {
        APB1_GRP1_EnableClock(RCC_APB1ENR_TIM2EN);
      }
    else if (_TIMx == TIM3)
      {
        APB1_GRP1_EnableClock(RCC_APB1ENR_TIM3EN);
      }
    else if (_TIMx == TIM4)
      {
        APB1_GRP1_EnableClock(RCC_APB1ENR_TIM4EN);
      }
    else if (_TIMx == TIM5)
      {
        APB1_GRP1_EnableClock(RCC_APB1ENR_TIM5EN);
      }
    else if (_TIMx == TIM9)
      {
        APB2_GRP1_EnableClock(RCC_APB2ENR_TIM9EN);
      }
    else if (_TIMx == TIM10)
      {
        APB2_GRP1_EnableClock(RCC_APB2ENR_TIM10EN);
      }
    else if (_TIMx == TIM11)
      {
        APB2_GRP1_EnableClock(RCC_APB2ENR_TIM11EN);
      }
  }

  void SetAutoReload(uint32_t AutoReload)
  {
    WRITE_REG(_TIMx->ARR, AutoReload);
  }

  void GenerateEvent_UPDATE()
  {
    SET_BIT(_TIMx->EGR, TIM_EGR_UG);
  }

  void EnableIT_UPDATE()
  {
    SET_BIT(_TIMx->DIER, TIM_DIER_UIE);
  }

  void EnableCounter()
  {
    SET_BIT(_TIMx->CR1, TIM_CR1_CEN);
  }

  void ClearFlag_UPDATE()
  {
    WRITE_REG(_TIMx->SR, ~(TIM_SR_UIF));
  }

  uint32_t IsActiveFlag_UPDATE()
  {
    return ((READ_BIT(_TIMx->SR, TIM_SR_UIF) == (TIM_SR_UIF)) ? 1UL : 0UL);
  }
};
