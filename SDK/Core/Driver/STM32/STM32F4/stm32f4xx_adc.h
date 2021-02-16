#pragma once

#ifdef STM32F4

#include <cstdint>

#include "PinNamesTypes.h"
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"

const PinMap PinMap_ADC[] = {
    {PA0, ADC1_BASE, STM_PIN_DEFINE_EXT(STM_MODE_ANALOG, PullNone, 0, 0, 0)},   // ADC1_IN0
    {PA1, ADC1_BASE, STM_PIN_DEFINE_EXT(STM_MODE_ANALOG, PullNone, 0, 1, 0)},   // ADC1_IN1
    {PA2, ADC1_BASE, STM_PIN_DEFINE_EXT(STM_MODE_ANALOG, PullNone, 0, 2, 0)},   // ADC1_IN2 // Connected to STDIO_UART_TX
    {PA3, ADC1_BASE, STM_PIN_DEFINE_EXT(STM_MODE_ANALOG, PullNone, 0, 3, 0)},   // ADC1_IN3 // Connected to STDIO_UART_RX
    {PA4, ADC1_BASE, STM_PIN_DEFINE_EXT(STM_MODE_ANALOG, PullNone, 0, 4, 0)},   // ADC1_IN4
    {PA5, ADC1_BASE, STM_PIN_DEFINE_EXT(STM_MODE_ANALOG, PullNone, 0, 5, 0)},   // ADC1_IN5 // Connected to LD2 [Green Led]
    {PA6, ADC1_BASE, STM_PIN_DEFINE_EXT(STM_MODE_ANALOG, PullNone, 0, 6, 0)},   // ADC1_IN6
    {PA7, ADC1_BASE, STM_PIN_DEFINE_EXT(STM_MODE_ANALOG, PullNone, 0, 7, 0)},   // ADC1_IN7
    {PB0, ADC1_BASE, STM_PIN_DEFINE_EXT(STM_MODE_ANALOG, PullNone, 0, 8, 0)},   // ADC1_IN8
    {PB1, ADC1_BASE, STM_PIN_DEFINE_EXT(STM_MODE_ANALOG, PullNone, 0, 9, 0)},   // ADC1_IN9
    {PC0, ADC1_BASE, STM_PIN_DEFINE_EXT(STM_MODE_ANALOG, PullNone, 0, 10, 0)},  // ADC1_IN10
    {PC1, ADC1_BASE, STM_PIN_DEFINE_EXT(STM_MODE_ANALOG, PullNone, 0, 11, 0)},  // ADC1_IN11
    {PC2, ADC1_BASE, STM_PIN_DEFINE_EXT(STM_MODE_ANALOG, PullNone, 0, 12, 0)},  // ADC1_IN12
    {PC3, ADC1_BASE, STM_PIN_DEFINE_EXT(STM_MODE_ANALOG, PullNone, 0, 13, 0)},  // ADC1_IN13
    {PC4, ADC1_BASE, STM_PIN_DEFINE_EXT(STM_MODE_ANALOG, PullNone, 0, 14, 0)},  // ADC1_IN14
    {PC5, ADC1_BASE, STM_PIN_DEFINE_EXT(STM_MODE_ANALOG, PullNone, 0, 15, 0)},  // ADC1_IN15
    {NC, NC, 0},
};

const PinMap PinMap_ADC_Internal[] = {
    {ADC_TEMP, ADC1_BASE, STM_PIN_DEFINE_EXT(STM_MODE_ANALOG, PullNone, 0, 16, 0)},
    {ADC_VREF, ADC1_BASE, STM_PIN_DEFINE_EXT(STM_MODE_ANALOG, PullNone, 0, 17, 0)},
    {ADC_VBAT, ADC1_BASE, STM_PIN_DEFINE_EXT(STM_MODE_ANALOG, PullNone, 0, 18, 0)},
    {NC, NC, 0},
};

enum ADC_SQR_REGOFFSET : uint32_t
{
  SQR1,
  SQR2,
  SQR3,
  SQR4
};

enum class ADCRank : uint32_t
{
  RANK1 = (SQR3 << 8U) | ADC_SQR3_SQ1_Pos,
  RANK2 = (SQR3 << 8U) | ADC_SQR3_SQ2_Pos,
  RANK3 = (SQR3 << 8U) | ADC_SQR3_SQ3_Pos,
  RANK4 = (SQR3 << 8U) | ADC_SQR3_SQ4_Pos,
  RANK5 = (SQR3 << 8U) | ADC_SQR3_SQ5_Pos,
  RANK6 = (SQR3 << 8U) | ADC_SQR3_SQ6_Pos,
  RANK7 = (SQR2 << 8U) | ADC_SQR2_SQ7_Pos,
  RANK8 = (SQR2 << 8U) | ADC_SQR2_SQ8_Pos,
  RANK9 = (SQR2 << 8U) | ADC_SQR2_SQ9_Pos,
  RANK10 = (SQR2 << 8U) | ADC_SQR2_SQ10_Pos,
  RANK11 = (SQR2 << 8U) | ADC_SQR2_SQ11_Pos,
  RANK12 = (SQR2 << 8U) | ADC_SQR2_SQ12_Pos,
  RANK13 = (SQR1 << 8U) | ADC_SQR1_SQ13_Pos,
  RANK14 = (SQR1 << 8U) | ADC_SQR1_SQ14_Pos,
  RANK15 = (SQR1 << 8U) | ADC_SQR1_SQ15_Pos,
  RANK16 = (SQR1 << 8U) | ADC_SQR1_SQ16_Pos,
};

enum class SampleTime : uint32_t
{
  _3CYCLES,
  _15CYCLES,
  _28CYCLES,
  _56CYCLES,
  _84CYCLES,
  _112CYCLES,
  _144CYCLES,
  _480CYCLES,
};

class ADCDriver
{
 private:
  GPIO         _gpio;
  PinName      _pin;
  ADC_TypeDef *_ADCx;
  uint32_t     _channel;

 public:
  ADCDriver(PinName pin, ADC_TypeDef *ADCx = ADC1) { init(pin, ADCx); }

  operator uint16_t()
  {
    return read_u12();
  }

  void init(PinName pin, ADC_TypeDef *ADCx = ADC1)
  {
    _ADCx = ADCx;

    _gpio.init(pin);
    _gpio.set_mode(GPIO::Mode::ANALOG);
    _gpio.set_pull(GPIO::Pull::NONE);

    _channel = get_channel(pin);

    if (!is_enabled())
      {
        enable_clock();
        set_common_path_internal_channel(ADC_CCR_VBATE);
        set_channel_sampling_time(SampleTime::_15CYCLES);
        enable();
      }
  }

  void enable_clock()
  {
    APB2_GRP1_EnableClock(RCC_APB2ENR_ADC1EN);
  }

  uint8_t get_channel(PinName pin)
  {
    if ((pin < 0xF0) || (pin >= 0x100))
      return STM_PIN_CHANNEL(pinmap_function(pin, PinMap_ADC));
    return STM_PIN_CHANNEL(pinmap_function(pin, PinMap_ADC_Internal));
  }

  uint16_t read_u12(void)
  {
    set_sequencer_ranks(ADCRank::RANK1);
    // ADC1->SQR3 = _channel << ADC_SQR3_SQ1_Pos;
    start_conversion();
    wait_until_end_of_conversion();
    return read_datareg();
  }

  uint32_t is_enabled() { return (READ_BIT(_ADCx->CR2, ADC_CR2_ADON) == (ADC_CR2_ADON)); }

  void enable() { SET_BIT(_ADCx->CR2, ADC_CR2_ADON); }

  uint16_t read_datareg()
  {
    __disable_irq();
    uint16_t tmp = READ_BIT(_ADCx->DR, ADC_DR_DATA);
    __enable_irq();
    return tmp;
  }

  void start_conversion() { SET_BIT(_ADCx->CR2, ADC_CR2_SWSTART); }

  uint32_t is_active_flag_EOC() { return (READ_BIT(_ADCx->SR, ADC_SR_EOC)) == (ADC_SR_EOC); }

  void wait_until_end_of_conversion()
  {
    while (!is_active_flag_EOC()) continue;
  }

  void set_channel_sampling_time(SampleTime SamplingTime)
  {
    switch (_channel < 10)
      {
        case true:
          SET_BIT(ADC1->SMPR2, ((uint32_t)SamplingTime) << (_channel * 3U));
          break;
        case false:
          SET_BIT(ADC1->SMPR1, ((uint32_t)SamplingTime) << ((_channel - 10U) * 3U));
          break;
      }
  }

  void set_sequencer_ranks(ADCRank Rank)
  {
    switch ((uint32_t)Rank >> 8U)
      {
        case SQR1:
          WRITE_REG(_ADCx->SQR1, _channel << ((uint32_t)Rank & 0x11111111U));
          break;
        case SQR2:
          WRITE_REG(_ADCx->SQR2, _channel << ((uint32_t)Rank & 0x11111111U));
          break;
        case SQR3:
          WRITE_REG(_ADCx->SQR3, _channel << ((uint32_t)Rank & 0x11111111U));
          break;
        // case 3:
        // _ADCx->SQR4 = _channel << ((uint32_t)Rank & 0x11111111U);
        // break;
        default:
          break;
      }
  }

  void set_common_path_internal_channel(uint32_t PathInternal)
  {
    MODIFY_REG(ADC1_COMMON->CCR, ADC_CCR_TSVREFE | ADC_CCR_VBATE, PathInternal);
  }
};

#endif  // STM32F4