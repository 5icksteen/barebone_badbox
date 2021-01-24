#pragma once

#include <codecvt>
#include <cstdint>
#include <cstdlib>

#include "USB_Common.h"

struct Microsoft_OS
{
  struct _String_Descriptor
  {
    const uint8_t bLength = 0x12;
    const DescriptorTypes bDescriptorType = DescriptorTypes::STRING;
    const uint16_t qwSignature[7] = {'M', 'S', 'F', 'T', '1', '0', '0'};
    const uint8_t bMS_VendorCode = 0x01;
    const uint8_t bPad = 0x00;
  } __attribute__((packed));

  struct _Compat_ID_Header_Section
  {
    const uint32_t dwLength;
    const uint16_t bcdVersion = VERSION_BCD(1, 0, 0);
    const uint16_t wIndex = 4;
    const uint8_t bCount = 1;
    const uint8_t : 8 * 7;  // RESERVED
  } __attribute__((packed));

  struct _Compat_ID_Function_Section
  {
    const uint8_t bFirstInterfaceNumber = 0;
    const uint8_t : 8 * 1;  // RESERVED
    const char8_t compatibleID[8] = u8"WINUSB";
    const char8_t subCompatibleID[8] = {};
    const uint8_t : 8 * 6;  // RESERVED
  } __attribute__((packed));

  struct _Compat_ID_Descriptor
  {
    _Compat_ID_Header_Section Compat_ID_Header_Section = {
        .dwLength = sizeof(_Compat_ID_Descriptor)};
    _Compat_ID_Function_Section Compat_ID_Function_Section;
  } __attribute__((packed));

  enum class PropertyDataTypes
  {
    REG_RESERVED,
    REG_SZ,
    REG_EXPAND_SZ,
    REG_BINARY,
    REG_DWORDLITTLE_ENDIAN,
    REG_DWORD_BIG_ENDIAN,
    REG_LINK,
    REG_MULTI_SZ
  };

  struct _Property_Header_Section
  {
    const uint32_t dwLength;
    const uint16_t bcdVersion = VERSION_BCD(1, 0, 0);
    const uint16_t wIndex = 0x0005;
    const uint16_t wCount = 0x0000;
  } __attribute__((packed));

#define PropertyName u"DeviceInterfaceGUID"
#define PropertyData u"{00000000-0000-0000-0000-000000000000}"

  struct _Property_Custom_Section
  {
    const uint32_t dwSize = sizeof(_Property_Custom_Section);
    const PropertyDataTypes dwPropertyDataType;
    const uint16_t wPropertyNameLength = sizeof(bPropertyName);
    static constexpr char16_t bPropertyName[] = PropertyName;
    const uint32_t dwPropertyDataLength = sizeof(bPropertyData);
    static constexpr char16_t bPropertyData[] = PropertyData;
  } __attribute__((packed));

  struct _Properties_Descriptor
  {
    _Property_Header_Section Property_Header_Section = {
        .dwLength = sizeof(_Properties_Descriptor),
        .wCount = 0x0001};
    _Property_Custom_Section Property_Custom_Section = {
        .dwPropertyDataType = PropertyDataTypes::REG_MULTI_SZ};
  } __attribute__((packed));
};
