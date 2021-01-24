#pragma once

#include "stm32f4xx.h"

class RTCControl
{
 public:
  void HSE_EnableBypass() { SET_BIT(RCC->CR, RCC_CR_HSEBYP); }
  void HSE_DisableBypass() { CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP); }
  void HSE_Enable()
  {
    SET_BIT(RCC->CR, RCC_CR_HSEON);
    while ((RCC->CR & RCC_CR_HSERDY) == 0) {}
  }
  void HSE_Disable() { CLEAR_BIT(RCC->CR, RCC_CR_HSEON); }
  uint32_t HSE_IsReady() { return (READ_BIT(RCC->CR, RCC_CR_HSERDY) == (RCC_CR_HSERDY)); }

  void HSI_Enable()
  {
    SET_BIT(RCC->CR, RCC_CR_HSION);
    while ((RCC->CR & RCC_CR_HSIRDY) == 0) {}
  }
  void HSI_Disable() { CLEAR_BIT(RCC->CR, RCC_CR_HSION); }
  uint32_t HSI_IsReady() { return (READ_BIT(RCC->CR, RCC_CR_HSIRDY) == (RCC_CR_HSIRDY)); }
  uint32_t HSI_GetCalibration() { return (uint32_t)(READ_BIT(RCC->CR, RCC_CR_HSICAL) >> RCC_CR_HSICAL_Pos); }
  void HSI_SetCalibTrimming(uint32_t Value) { MODIFY_REG(RCC->CR, RCC_CR_HSITRIM, Value << RCC_CR_HSITRIM_Pos); }
  uint32_t HSI_GetCalibTrimming() { return (uint32_t)(READ_BIT(RCC->CR, RCC_CR_HSITRIM) >> RCC_CR_HSITRIM_Pos); }

  void LSE_Enable()
  {
    SET_BIT(RCC->BDCR, RCC_BDCR_LSEON);
    while ((RCC->CR & RCC_BDCR_LSERDY) == 0) {}
  }
  void LSE_Disable() { CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEON); }
  void LSE_EnableBypass() { SET_BIT(RCC->BDCR, RCC_BDCR_LSEBYP); }
  void LSE_DisableBypass() { CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEBYP); }
  uint32_t LSE_IsReady() { return (READ_BIT(RCC->BDCR, RCC_BDCR_LSERDY) == (RCC_BDCR_LSERDY)); }

  void LSI_Enable()
  {
    SET_BIT(RCC->CSR, RCC_CSR_LSION);
    while ((RCC->CR & RCC_CSR_LSIRDY) == 0) {}
  }
  void LSI_Disable() { CLEAR_BIT(RCC->CSR, RCC_CSR_LSION); }
  uint32_t LSI_IsReady() { return (READ_BIT(RCC->CSR, RCC_CSR_LSIRDY) == (RCC_CSR_LSIRDY)); }

  // enum class ClockSource
  // {
  //     NONE,
  //     LSE = RCC_BDCR_RTCSEL_0,
  //     LSI = RCC_BDCR_RTCSEL_1,
  //     HSE = RCC_BDCR_RTCSEL
  // };

  enum class SysClockSource
  {
    HSI = RCC_CFGR_SW_HSI,
    HSE = RCC_CFGR_SW_HSE,
    PLL = RCC_CFGR_SW_PLL,
#if defined(RCC_CFGR_SW_PLLR)
    PLLR = RCC_CFGR_SW_PLLR
#endif /* RCC_CFGR_SW_PLLR */
  };
  void SetSysClkSource(SysClockSource Source) { MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, (uint32_t)Source); }
  uint32_t GetSysClkSource() { return (uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_SWS)); }

  enum class AHBPrescaler
  {
    DIV1 = RCC_CFGR_HPRE_DIV1,
    DIV2 = RCC_CFGR_HPRE_DIV2,
    DIV4 = RCC_CFGR_HPRE_DIV4,
    DIV8 = RCC_CFGR_HPRE_DIV8,
    DIV16 = RCC_CFGR_HPRE_DIV16,
    DIV64 = RCC_CFGR_HPRE_DIV64,
    DIV128 = RCC_CFGR_HPRE_DIV128,
    DIV256 = RCC_CFGR_HPRE_DIV256,
    DIV512 = RCC_CFGR_HPRE_DIV512
  };
  void SetAHBPrescaler(AHBPrescaler Prescaler) { MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE, (uint32_t)Prescaler); }
  AHBPrescaler GetAHBPrescaler() { return (AHBPrescaler)(READ_BIT(RCC->CFGR, RCC_CFGR_HPRE)); }

  enum class APB1Prescaler
  {
    DIV1 = RCC_CFGR_PPRE1_DIV1,
    DIV2 = RCC_CFGR_PPRE1_DIV2,
    DIV4 = RCC_CFGR_PPRE1_DIV4,
    DIV8 = RCC_CFGR_PPRE1_DIV8,
    DIV16 = RCC_CFGR_PPRE1_DIV16
  };
  void SetAPB1Prescaler(APB1Prescaler Prescaler) { MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE1, (uint32_t)Prescaler); }
  APB1Prescaler GetAPB1Prescaler() { return (APB1Prescaler)(READ_BIT(RCC->CFGR, RCC_CFGR_PPRE1)); }

  enum class APB2Prescaler
  {
    DIV1 = RCC_CFGR_PPRE2_DIV1,
    DIV2 = RCC_CFGR_PPRE2_DIV2,
    DIV4 = RCC_CFGR_PPRE2_DIV4,
    DIV8 = RCC_CFGR_PPRE2_DIV8,
    DIV16 = RCC_CFGR_PPRE2_DIV16
  };
  void SetAPB2Prescaler(APB2Prescaler Prescaler) { MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE2, (uint32_t)Prescaler); }
  APB2Prescaler GetAPB2Prescaler() { return (APB2Prescaler)(READ_BIT(RCC->CFGR, RCC_CFGR_PPRE2)); }

  void PLL_Enable()
  {
    SET_BIT(RCC->CR, RCC_CR_PLLON);
    while ((RCC->CR & RCC_CR_PLLRDY) == 0) {}
  }
  void PLL_Disable() { CLEAR_BIT(RCC->CR, RCC_CR_PLLON); }
  uint32_t PLL_IsReady() { return (READ_BIT(RCC->CR, RCC_CR_PLLRDY) == (RCC_CR_PLLRDY)); }

  enum class PLLSource
  {
    HSI = RCC_PLLCFGR_PLLSRC_HSI,
    HSE = RCC_PLLCFGR_PLLSRC_HSE
  };
  // void PLL_ConfigDomain_SYS(PLLSource Source, uint32_t PLLM, uint32_t PLLN, uint32_t PLLP_R)
  // {
  //     MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC | RCC_PLLCFGR_PLLM | RCC_PLLCFGR_PLLN,
  //                (uint32_t)Source | PLLM | PLLN << RCC_PLLCFGR_PLLN_Pos);
  //     MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLP, PLLP_R);
  // }
  void SetPLLSource(PLLSource Source)
  {
    MODIFY_REG(RCC->PLLCFGR,
               RCC_PLLCFGR_PLLSRC,
               (uint32_t)Source);
  }
  void SetPLLM(uint32_t PLLM)
  {
    MODIFY_REG(RCC->PLLCFGR,
               RCC_PLLCFGR_PLLM,
               PLLM << RCC_PLLCFGR_PLLM_Pos);
  }
  void SetPLLN(uint32_t PLLN)
  {
    MODIFY_REG(RCC->PLLCFGR,
               RCC_PLLCFGR_PLLN,
               PLLN << RCC_PLLCFGR_PLLN_Pos);
  }
  void SetPLLP(uint32_t PLLP)
  {
    MODIFY_REG(RCC->PLLCFGR,
               RCC_PLLCFGR_PLLP,
               PLLP << RCC_PLLCFGR_PLLP_Pos);
  }
  void SetPLLQ(uint32_t PLLQ)
  {
    MODIFY_REG(RCC->PLLCFGR,
               RCC_PLLCFGR_PLLQ,
               PLLQ << RCC_PLLCFGR_PLLQ_Pos);
  }
};