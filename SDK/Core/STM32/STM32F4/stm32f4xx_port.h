#pragma once

#ifdef STM32F4

#include <cstdint>

#include "stm32f4xx.h"
#include "stm32f4xx_bus.h"

enum PortName
{
  FirstPort = 0x00,
  PortA = FirstPort,
  PortB,
#if defined GPIOC
  PortC,
#endif
#if defined GPIOD
  PortD,
#endif
#if defined GPIOE
  PortE,
#endif
#if defined GPIOF
  PortF,
#endif
#if defined GPIOG
  PortG,
#endif
#if defined GPIOH
  PortH,
#endif
#if defined GPIOI
  PortI,
#endif
#if defined GPIOJ
  PortJ,
#endif
#if defined GPIOK
  PortK,
#endif
#if defined GPIOZ
  PortZ,
#endif
  PortNum
};

constexpr GPIO_TypeDef *GPIOPort[PortNum] = {
    GPIOA,
    GPIOB,
#if defined GPIOC
    GPIOC,
#endif
#if defined GPIOD
    GPIOD,
#endif
#if defined GPIOE
    GPIOE,
#endif
#if defined GPIOF
    GPIOF,
#endif
#if defined GPIOG
    GPIOG,
#endif
#if defined GPIOH
    GPIOH,
#endif
#if defined GPIOI
    GPIOI,
#endif
#if defined GPIOJ
    GPIOJ,
#endif
#if defined GPIOK
    GPIOK,
#endif
#if defined GPIOZ
    GPIOZ,
#endif
};

constexpr uint32_t get_gpio_port(uint32_t pin)
{
  return (pin >> 4UL);
}

/* Enable GPIO clock and return GPIO base address */
constexpr GPIO_TypeDef *set_gpio_port_clock(uint32_t port_idx)
{
  GPIO_TypeDef *gpioPort = 0;
  switch (port_idx)
    {
      case PortA:
        gpioPort = GPIOA;
        AHB1_GRP1_EnableClock(RCC_AHB1ENR_GPIOAEN);
        break;
      case PortB:
        gpioPort = GPIOB;
        AHB1_GRP1_EnableClock(RCC_AHB1ENR_GPIOBEN);
        break;
#if defined GPIOC
      case PortC:
        gpioPort = GPIOC;
        AHB1_GRP1_EnableClock(RCC_AHB1ENR_GPIOCEN);
        break;
#endif
#if defined GPIOD
      case PortD:
        gpioPort = GPIOD;
        AHB1_GRP1_EnableClock(RCC_AHB1ENR_GPIODEN);
        break;
#endif
#if defined GPIOE
      case PortE:
        gpioPort = GPIOE;
        AHB1_GRP1_EnableClock(RCC_AHB1ENR_GPIOEEN);
        break;
#endif
#if defined GPIOF
      case PortF:
        gpioPort = GPIOF;
        AHB1_GRP1_EnableClock(RCC_AHB1ENR_GPIOFEN);
        break;
#endif
#if defined GPIOG
      case PortG:
        gpioPort = GPIOG;
        AHB1_GRP1_EnableClock(RCC_AHB1ENR_GPIOGEN);
        break;
#endif
#if defined GPIOH
      case PortH:
        gpioPort = GPIOH;
        AHB1_GRP1_EnableClock(RCC_AHB1ENR_GPIOHEN);
        break;
#endif
#if defined GPIOI
      case PortI:
        gpioPort = GPIOI;
        AHB1_GRP1_EnableClock(RCC_AHB1ENR_GPIOIEN);
        break;
#endif
#if defined GPIOJ
      case PortJ:
        gpioPort = GPIOJ;
        AHB1_GRP1_EnableClock(RCC_AHB1ENR_GPIOJEN);
        break;
#endif
#if defined GPIOK
      case PortK:
        gpioPort = GPIOK;
        AHB1_GRP1_EnableClock(RCC_AHB1ENR_GPIOKEN);
        break;
#endif
#if defined GPIOZ
      case PortZ:
        gpioPort = GPIOZ;
        AHB1_GRP1_EnableClock(RCC_AHB1ENR_GPIOZEN);
        break;
#endif
      default:
        // wrong port number
        // TODO: error management
        gpioPort = 0;
        break;
    }
  return gpioPort;
}

#endif  // STM32F4
