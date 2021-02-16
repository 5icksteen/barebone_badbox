#pragma once

#include "stm32f4xx.h"

enum class RegulatorVoltage
{
  SCALE3 = PWR_CR_VOS_0,
  SCALE2 = PWR_CR_VOS_1,
  SCALE1 = PWR_CR_VOS_0 | PWR_CR_VOS_1
};

void PWR_SetRegulVoltageScaling(RegulatorVoltage VoltageScaling)
{
  MODIFY_REG(PWR->CR, PWR_CR_VOS, (uint32_t)VoltageScaling);
}