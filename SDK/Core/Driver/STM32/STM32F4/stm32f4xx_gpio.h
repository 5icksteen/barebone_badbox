#pragma once

#ifdef STM32F4

#include <cstdint>

#include "stm32f4xx.h"
#include "stm32f4xx_bus.h"
#include "stm32f4xx_pin.h"

class GPIO
{
 protected:
  GPIO_TypeDef* port_;
  std::uint32_t pin_;

 public:
  enum class Mode
  {
    INPUT,
    OUTPUT,
    ALTERNATE,
    ANALOG
  };
  enum class OutputType
  {
    PUSHPULL,
    OPENDRAIN
  };
  enum class Speed
  {
    LOW,
    MEDIUM,
    HIGH,
    VERY_HIGH
  };
  enum class Pull
  {
    NONE,
    UP,
    DOWN
  };
  enum class AltFunc
  {
    AF0,
    AF1,
    AF2,
    AF3,
    AF4,
    AF5,
    AF6,
    AF7,
    AF8,
    AF9,
    AF10,
    AF11,
    AF12,
    AF13,
    AF14,
    AF15
  };
  enum class Polarity
  {
    POSITIVE,
    NEGATIVE
  };
  enum class State
  {
    LOW,
    HIGH,
    FALL,
    RISE,
  };

  GPIO& init(PinName pin)
  {
    port_ = set_gpio_port_clock(get_gpio_port(pin));
    pin_ = get_gpio_pin(pin);
    return *this;
  }

  //--------------------------------------------------------------------------
  // Mode
  //--------------------------------------------------------------------------
  void set_mode(Mode mode)
  {
    MODIFY_REG(port_->MODER,
               (GPIO_MODER_MODER0 << (POSITION_VAL(pin_) * 2U)),
               ((std::uint32_t)mode << (POSITION_VAL(pin_) * 2U)));
  }
  Mode get_mode()
  {
    return (Mode)(READ_BIT(port_->MODER,
                           (GPIO_MODER_MODER0 << (POSITION_VAL(pin_) * 2U)))
                  >> (POSITION_VAL(pin_) * 2U));
  }

  //--------------------------------------------------------------------------
  // Output Type
  //--------------------------------------------------------------------------
  void set_output_type(OutputType type)
  {
    MODIFY_REG(port_->OTYPER, pin_, (pin_ * (std::uint32_t)type));
  }
  OutputType get_output_type()
  {
    return (OutputType)(READ_BIT(port_->OTYPER, pin_) >> POSITION_VAL(pin_));
  }

  //--------------------------------------------------------------------------
  // Speed
  //--------------------------------------------------------------------------
  void set_speed(Speed speed)
  {
    MODIFY_REG(port_->OSPEEDR, (GPIO_OSPEEDER_OSPEEDR0 << (POSITION_VAL(pin_) * 2U)), ((std::uint32_t)speed << (POSITION_VAL(pin_) * 2U)));
  }
  Speed get_speed()
  {
    return (Speed)(READ_BIT(port_->OSPEEDR,
                            (GPIO_OSPEEDER_OSPEEDR0 << (POSITION_VAL(pin_) * 2U)))
                   >> (POSITION_VAL(pin_) * 2U));
  }

  //--------------------------------------------------------------------------
  // Pull
  //--------------------------------------------------------------------------
  void set_pull(Pull pull)
  {
    MODIFY_REG(port_->PUPDR, (GPIO_PUPDR_PUPDR0 << (POSITION_VAL(pin_) * 2U)), ((std::uint32_t)pull << (POSITION_VAL(pin_) * 2U)));
  }

  Pull get_pull()
  {
    return (Pull)(READ_BIT(port_->PUPDR,
                           (GPIO_PUPDR_PUPDR0 << (POSITION_VAL(pin_) * 2U)))
                  >> (POSITION_VAL(pin_) * 2U));
  }

  //--------------------------------------------------------------------------
  // Alternate Function
  //--------------------------------------------------------------------------
  // TODO:
  void set_alternate(AltFunc alt)
  {
    if (POSITION_VAL(pin_) < 0x00000008U)
      {
        MODIFY_REG(port_->AFR[0], (GPIO_AFRL_AFSEL0 << (POSITION_VAL(pin_) * 4U)), ((std::uint32_t)alt << (POSITION_VAL(pin_) * 4U)));
      }
    else
      {
        MODIFY_REG(port_->AFR[1], (GPIO_AFRH_AFSEL8 << (POSITION_VAL(pin_ >> 8U) * 4U)), ((std::uint32_t)alt << (POSITION_VAL(pin_ >> 8U) * 4U)));
      }
  }
  AltFunc get_alternate()
  {
    if (POSITION_VAL(pin_) < 0x00000008U)
      {
        return (AltFunc)(READ_BIT(port_->AFR[0],
                                  (GPIO_AFRL_AFSEL0 << (POSITION_VAL(pin_) * 4U)))
                         >> (POSITION_VAL(pin_) * 4U));
      }
    else
      {
        return (AltFunc)(READ_BIT(port_->AFR[1],
                                  (GPIO_AFRH_AFSEL8 << (POSITION_VAL(pin_ >> 8U) * 4U)))
                         >> (POSITION_VAL(pin_ >> 8U) * 4U));
      }
  }

  //--------------------------------------------------------------------------
  // Lock
  //--------------------------------------------------------------------------
  void lock()
  {
    __IO std::uint32_t temp;
    WRITE_REG(port_->LCKR, GPIO_LCKR_LCKK | pin_);
    WRITE_REG(port_->LCKR, pin_);
    WRITE_REG(port_->LCKR, GPIO_LCKR_LCKK | pin_);
    temp = READ_REG(port_->LCKR);
    (void)temp;
  }
  std::uint32_t is_pin_locked()
  {
    return (READ_BIT(port_->LCKR, pin_) == (pin_));
  }

  std::uint32_t is_any_pin_locked()
  {
    return (READ_BIT(port_->LCKR, GPIO_LCKR_LCKK) == (GPIO_LCKR_LCKK));
  }

  //--------------------------------------------------------------------------
  // Input
  //--------------------------------------------------------------------------
  // std::uint32_t read_input_port() {
  //     return (std::uint32_t)(READ_REG(port_->IDR));
  // }
  std::uint32_t is_input_set()
  {
    return (READ_BIT(port_->IDR, pin_) == (pin_));
  }
  std::uint32_t read_input()
  {
    return ((is_input_set()) & 0x01);
  }

  //--------------------------------------------------------------------------
  // Output
  //--------------------------------------------------------------------------
  // void write_output_port(std::uint32_t PortValue) {
  //     WRITE_REG(port_->ODR, PortValue);
  // }
  // std::uint32_t read_output_port() {
  //     return (std::uint32_t)(READ_REG(port_->ODR));
  // }
  std::uint32_t is_output_set()
  {
    return (READ_BIT(port_->ODR, pin_) == (pin_));
  }
  std::uint32_t read_output()
  {
    return ((is_output_set()) & 0x01);
  }
  void set_output()
  {
    WRITE_REG(port_->BSRR, pin_);
  }
  void reset_output()
  {
    WRITE_REG(port_->BSRR, (pin_ << 16));
  }
  void toggle_output()
  {
    WRITE_REG(port_->ODR, READ_REG(port_->ODR) ^ pin_);
  }
  void write_output(std::uint32_t value)
  {
    if (value == 1)
      {
        set_output();
      }
    else
      {
        reset_output();
      }
  }
};

#endif  // STM32F4