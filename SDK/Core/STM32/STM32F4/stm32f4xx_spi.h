#pragma once

#include "target.h"

class SPI
{
  SPI_TypeDef *SPIx;

  enum
  {
    MOSI,
    MISO,
    SCK
  };
  GPIO gpio_[3];

  // struct {
  //     uint32_t TransferDirection;
  //     uint32_t Mode;
  //     uint32_t DataWidth;
  //     uint32_t ClockPolarity;
  //     uint32_t ClockPhase;
  //     uint32_t NSS;
  //     uint32_t BaudRate;
  //     uint32_t BitOrder;
  //     uint32_t CRCCalculation;
  //     uint32_t CRCPoly;
  // } SPI_InitTypeDef;

 public:
  enum class Mode
  {
    SLAVE,
    MASTER = SPI_CR1_MSTR | SPI_CR1_SSI
  };

  enum class Protocol
  {
    MOTOROLA,
    TI = SPI_CR2_FRF
  };

  enum class Phase
  {
    _1EDGE,
    _2EDGE = SPI_CR1_CPHA
  };

  enum class Polarity
  {
    LOW,
    HIGH = SPI_CR1_CPOL
  };

  enum class BaudRatePrescaler
  {
    DIV2,
    DIV4 = SPI_CR1_BR_0,
    DIV8 = SPI_CR1_BR_1,
    DIV16 = SPI_CR1_BR_1 | SPI_CR1_BR_0,
    DIV32 = SPI_CR1_BR_2,
    DIV64 = SPI_CR1_BR_2 | SPI_CR1_BR_0,
    DIV128 = SPI_CR1_BR_2 | SPI_CR1_BR_1,
    DIV256 = SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0
  };

  enum class BitOrder
  {
    MSB_FIRST,
    LSB_FIRST = SPI_CR1_LSBFIRST
  };

  enum class TransferMode
  {
    FULL_DUPLEX,
    SIMPLEX_RX = SPI_CR1_RXONLY,
    HALF_DUPLEX_RX = SPI_CR1_BIDIMODE,
    HALF_DUPLEX_TX = SPI_CR1_BIDIMODE | SPI_CR1_BIDIOE
  };

  enum class NSSMode
  {
    HARD_INPUT,
    SOFT = SPI_CR1_SSM,
    HARD_OUTPUT = ((uint32_t)SPI_CR2_SSOE << 16U),
  };

  enum class DataWidth
  {
    _8BIT,
    _16BIT = SPI_CR1_DFF
  };

  SPI(PinName mosi, PinName miso, PinName sck)
  {
    gpio_[MOSI].init(mosi);
    gpio_[MOSI].set_mode(GPIO::Mode::ALTERNATE);
    gpio_[MOSI].set_speed(GPIO::Speed::VERY_HIGH);
    gpio_[MOSI].set_alternate(GPIO::AltFunc::AF5);
    gpio_[MISO].init(miso);
    gpio_[MISO].set_mode(GPIO::Mode::ALTERNATE);
    gpio_[MISO].set_speed(GPIO::Speed::VERY_HIGH);
    gpio_[MISO].set_alternate(GPIO::AltFunc::AF5);
    gpio_[SCK].init(sck);
    gpio_[SCK].set_mode(GPIO::Mode::ALTERNATE);
    gpio_[SCK].set_speed(GPIO::Speed::VERY_HIGH);
    gpio_[SCK].set_alternate(GPIO::AltFunc::AF5);

    this->set_group(SPI1);
    this->enable_clock();
    this->enable();
    this->set_mode(SPI::Mode::MASTER);
    this->set_clock_phase(SPI::Phase::_1EDGE);
    this->set_clock_polarity(SPI::Polarity::LOW);
    this->set_baud_rate_prescaler(SPI::BaudRatePrescaler::DIV2);
    this->set_transfer_bit_order(SPI::BitOrder::MSB_FIRST);
    this->set_transfer_direction(SPI::TransferMode::HALF_DUPLEX_TX);
    this->set_data_width(SPI::DataWidth::_16BIT);
    this->set_nss_mode(SPI::NSSMode::SOFT);
  }

  void set_group(SPI_TypeDef *group)
  {
    SPIx = group;
  }

  void enable_clock()
  {
    // APB2_GRP1_EnableClock(RCC_APB2ENR_SPI1EN);
  }

  void disable_clock()
  {
    // APB2_GRP1_DisableClock(RCC_APB2ENR_SPI1EN);
  }

  void enable()
  {
    SET_BIT(SPIx->CR1, SPI_CR1_SPE);
  }

  void disable()
  {
    CLEAR_BIT(SPIx->CR1, SPI_CR1_SPE);
  }

  uint32_t is_enabled()
  {
    return ((READ_BIT(SPIx->CR1, SPI_CR1_SPE) == (SPI_CR1_SPE)) ? 1UL : 0UL);
  }

  void set_mode(SPI::Mode Mode)
  {
    MODIFY_REG(SPIx->CR1, SPI_CR1_MSTR | SPI_CR1_SSI, (uint32_t)Mode);
  }

  SPI::Mode get_mode()
  {
    return (SPI::Mode)(READ_BIT(SPIx->CR1, SPI_CR1_MSTR | SPI_CR1_SSI));
  }

  // void set_standard(uint32_t Standard) {
  //     MODIFY_REG(SPIx->CR2, SPI_CR2_FRF, Standard);
  // }

  // uint32_t get_standard() {
  //     return (uint32_t)(READ_BIT(SPIx->CR2, SPI_CR2_FRF));
  // }

  void set_clock_phase(SPI::Phase ClockPhase)
  {
    MODIFY_REG(SPIx->CR1, SPI_CR1_CPHA, (uint32_t)ClockPhase);
  }

  SPI::Phase get_clock_phase()
  {
    return (SPI::Phase)(READ_BIT(SPIx->CR1, SPI_CR1_CPHA));
  }

  void set_clock_polarity(SPI::Polarity ClockPolarity)
  {
    MODIFY_REG(SPIx->CR1, SPI_CR1_CPOL, (uint32_t)ClockPolarity);
  }

  SPI::Polarity get_clock_polarity()
  {
    return (SPI::Polarity)(READ_BIT(SPIx->CR1, SPI_CR1_CPOL));
  }

  void set_baud_rate_prescaler(SPI::BaudRatePrescaler BaudRate)
  {
    MODIFY_REG(SPIx->CR1, SPI_CR1_BR, (uint32_t)BaudRate);
  }

  SPI::BaudRatePrescaler get_baud_rate_prescaler()
  {
    return (SPI::BaudRatePrescaler)(READ_BIT(SPIx->CR1, SPI_CR1_BR));
  }

  void set_transfer_bit_order(SPI::BitOrder BitOrder)
  {
    MODIFY_REG(SPIx->CR1, SPI_CR1_LSBFIRST, (uint32_t)BitOrder);
  }

  SPI::BitOrder get_transfer_bit_order()
  {
    return (SPI::BitOrder)(READ_BIT(SPIx->CR1, SPI_CR1_LSBFIRST));
  }

  void set_transfer_direction(SPI::TransferMode TransferDirection)
  {
    MODIFY_REG(SPIx->CR1, SPI_CR1_RXONLY | SPI_CR1_BIDIMODE | SPI_CR1_BIDIOE, (uint32_t)TransferDirection);
  }

  SPI::TransferMode get_transfer_direction()
  {
    return (SPI::TransferMode)(READ_BIT(SPIx->CR1, SPI_CR1_RXONLY | SPI_CR1_BIDIMODE | SPI_CR1_BIDIOE));
  }

  void set_data_width(SPI::DataWidth DataWidth)
  {
    MODIFY_REG(SPIx->CR1, SPI_CR1_DFF, (uint32_t)DataWidth);
  }

  SPI::DataWidth get_data_width()
  {
    return (SPI::DataWidth)(READ_BIT(SPIx->CR1, SPI_CR1_DFF));
  }

  void set_nss_mode(SPI::NSSMode NSS)
  {
    MODIFY_REG(SPIx->CR1, SPI_CR1_SSM, (uint32_t)NSS);
    MODIFY_REG(SPIx->CR2, SPI_CR2_SSOE, ((uint32_t)((uint32_t)NSS >> 16U)));
  }

  SPI::NSSMode get_nss_mode()
  {
    register uint32_t Ssm = (READ_BIT(SPIx->CR1, SPI_CR1_SSM));
    register uint32_t Ssoe = (READ_BIT(SPIx->CR2, SPI_CR2_SSOE) << 16U);
    return (SPI::NSSMode)(Ssm | Ssoe);
  }

  uint8_t ReceiveData8()
  {
    return (uint8_t)(READ_REG(SPIx->DR));
  }
  uint8_t ReceiveData8()
  {
    return (uint8_t)(READ_REG(SPIx->DR));
  }
  void TransmitData8(uint8_t TxData)
  {
    *(__IO uint8_t *)&SPIx->DR = TxData;
  }
  void TransmitData16(uint16_t TxData)
  {
    *(__IO uint16_t *)&SPIx->DR = TxData;
  }
  void wait_for_transmition_complete()
  {
    while ((SPIx->SR & SPI_SR_TXE) != SPI_SR_TXE) {}
    while ((SPIx->SR & SPI_SR_BSY) == SPI_SR_BSY) {}
  }
};
