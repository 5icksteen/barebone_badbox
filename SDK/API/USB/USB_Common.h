#pragma once

#include <cstddef>
#include <cstdint>

template <typename T>
consteval size_t byteof(const T *string)
{
  return (std::char_traits<T>::length(string) + 1) * 2;
}

consteval uint16_t VERSION_BCD(uint16_t maj, uint16_t min, uint16_t rev)
{
  return (((maj & 0xFF) << 8) | ((min & 0x0F) << 4) | (rev & 0x0F));
}

enum class DescriptorTypes : uint8_t
{
  DEVICE = 0x01,
  CONFIGURATION,
  STRING,
  INTERFACE,
  ENDPOINT,
  // DEVICE_QUALIFIER,
  // OTHER_SPEED_CONFIGURATION,
  // INTERFACE_POWER,
  // OTG,
  // DEBUG,
  // INTERFASEASSOC,
  DFU_FUNCTIONAL = 0x21,
  // CS_INTERFACE = 0x24,
  // CS_ENDPOINT = 0x25
};

constexpr uint8_t USB_Configuration_MaxPower(uint8_t mA)
{
  return ((mA) >> 1);
}

enum class USB_Configuration_Attributes : uint8_t
{
  SELFPOWERED = 0x40,
  RESERVED = 0x80
};

enum class USB_Endpoint_Direction : uint8_t
{
  IN = 0x00,
  OUT = 0x80
};

enum class USB_Endpoint_Types : uint8_t
{
  Control,
  Isochronus,
  Bulk,
  Interrupt
};

enum class USB_Endpoint_Attributes : uint8_t
{
  No_Sync = 0x00,
  Async = 0x04,
  Adaptive = 0x08,
  Sync = 0x0C
};

enum class USB_Endpoint_Usage : uint8_t
{
  Data = 0x00,
  Feedback = 0x10,
  Implicit_Feedback = 0x20
};

struct Device_Descriptor
{
  const uint8_t bLength = sizeof(Device_Descriptor);
  const DescriptorTypes bDescriptorType = DescriptorTypes::CONFIGURATION;
  const uint16_t bcdUSB = VERSION_BCD(2, 0, 0);
  const uint8_t bDeviceClass = 0x00;
  const uint8_t bDeviceSubClass = 0x00;
  const uint8_t bDeviceProtocol = 0x00;
  const uint8_t bMaxPacketSize0;
  const uint16_t idVendor;
  const uint16_t idProduct;
  const uint16_t bcdDevice;
  const uint8_t iManufacturer;
  const uint8_t iProduct;
  const uint8_t iSerialNumber;
  const uint8_t bNumConfigurations;
};