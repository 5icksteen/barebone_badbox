#pragma once

#include <cstdint>

#include "USB_Common.h"

enum class DFU_DeviceClass : uint8_t
{
  USB_CLASS_DFU = 0xFE
};

enum class DFU_DeviceSubClass : uint8_t
{
  USB_SUBCLASS_DFU = 0x01
};

enum class DFU_InterfaceProtocol : uint8_t
{
  DFU_Runtime = 0x01,
  DFU_Mode = 0x02
};

enum class DFU_Request
{
  DFU_DETACH,
  DFU_DNLOAD,
  DFU_UPLOAD,
  DFU_GETSTATUS,
  DFU_CLRSTATUS,
  DFU_GETSTATE,
  DFU_ABORT
};

enum class DFU_Attributes
{
  bitCanDnload = 0x01,
  bitCanUpload = 0x02,
  bitWillDetach = 0x04,
  bitManifestationTolerant = 0x08
};

enum class DFU_Device_Status
{
  OK,
  errTARGET,
  errFILE,
  errWRITE,
  errERASE,
  errCHECK_ERASED,
  errPROG,
  errVERIFY,
  errADDRESS,
  errNOTDONE,
  errFIRMWARE,
  errVENDOR,
  errUSBR,
  errPOR,
  errUNKNOWN,
  errSTALLEDPKY
};

enum class DFU_Device_State
{
  appIDLE,
  appDETACH,
  dfuIDLE,
  dfuDNLOAD_SYNC,
  dfuDNBUSY,
  dfuDNLOAD_IDLE,
  dfuMANIFEST_SYNC,
  dfuMANIFEST,
  dfuMANIFEST_WAIT_RESET,
  dfuUPLOAD_IDLE,
  dfuERROR
};

struct RunTime_DFU_Interface_Descriptor
{
  const uint8_t bLength = sizeof(RunTime_DFU_Interface_Descriptor);
  const DescriptorTypes bDescriptorType = DescriptorTypes::INTERFACE;
  const uint8_t bInterfaceNumber;
  const uint8_t bAlternateSetting = 0x00;
  const uint8_t bNumEndpoints = 0x00;
  const DFU_DeviceClass bInterfaceClass = DFU_DeviceClass::USB_CLASS_DFU;
  const DFU_DeviceSubClass bInterfaceSubClass = DFU_DeviceSubClass::USB_SUBCLASS_DFU;
  const DFU_InterfaceProtocol bInterfaceProtocol = DFU_InterfaceProtocol::DFU_Runtime;
  const uint8_t iInterface;
};

struct RunTime_DFU_Functional_Descriptor
{
  const uint8_t bLength = sizeof(RunTime_DFU_Functional_Descriptor);
  const DescriptorTypes bDescriptorType = DescriptorTypes::DFU_FUNCTIONAL;
  const uint8_t bmAttributes;
  const uint16_t wDetachTimeout;
  const uint16_t wTransferSize;
  const uint16_t bcdDFUVersion = VERSION_BCD(1, 1, 0);
};

struct DFU_Mode_Device_Descriptor : public Device_Descriptor
{  // TODO:
  const uint8_t bLength = sizeof(DFU_Mode_Device_Descriptor);
  const DescriptorTypes bDescriptorType = DescriptorTypes::DEVICE;
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
  const uint8_t bNumConfigurations = 0x01;
};

struct DFU_Mode_Interface_Descriptor
{
  const uint8_t bLength = sizeof(DFU_Mode_Interface_Descriptor);
  const DescriptorTypes bDescriptorType = DescriptorTypes::INTERFACE;
  const uint8_t bInterfaceNumber = 0x00;
  const uint8_t bAlternateSetting;
  const uint8_t bNumEndpoints = 0x00;
  const DFU_DeviceClass bInterfaceClass = DFU_DeviceClass::USB_CLASS_DFU;
  const DFU_DeviceSubClass bInterfaceSubClass = DFU_DeviceSubClass::USB_SUBCLASS_DFU;
  const DFU_InterfaceProtocol bInterfaceProtocol = DFU_InterfaceProtocol::DFU_Mode;
  const uint8_t iInterface;
};

struct DFU_GETSTATUS_Request
{
  uint8_t bStatus;
  uint8_t bPollTimeout;
  uint16_t wPollTimeout;
  uint8_t bState;
  uint8_t iString;
};

struct DFU_GETSTATE_Request
{
  uint8_t bState;
};
