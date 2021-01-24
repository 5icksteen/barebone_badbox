#pragma once

#include <cstdint>

class USBDevice
{
  enum class Request : uint8_t
  {
    GET_STATUS,
    CLEAR_FEATURE,
    _Reserved_for_future_use,
    SET_FEATURE,
    _reserved_for_future_use,
    SET_ADDRESS,
    GET_DESCRIPTOR,
    SET_DESCRIPTOR,
    GET_CONFIGURATION,
    SET_CONFIGURATION,
    GET_INTERFACE,
    SET_INTERFACE,
    SYNC_FRAME
  };

  void _Request_Switch_Template(Request req)
  {
    switch (req)
      {
        case Request::GET_STATUS:
        case Request::CLEAR_FEATURE:
        case Request::SET_FEATURE:
        case Request::SET_ADDRESS:
        case Request::GET_DESCRIPTOR:
        case Request::SET_DESCRIPTOR:
        case Request::GET_CONFIGURATION:
        case Request::SET_CONFIGURATION:
        case Request::GET_INTERFACE:
        case Request::SET_INTERFACE:
        case Request::SYNC_FRAME:
        default:
          break;
      }
  }

  enum class DescriptorTypes : uint8_t
  {
    DEVICE = 0x01,
    CONFIGURATION,
    STRING,
    INTERFACE,
    ENDPOINT,
    DFU_FUNCTIONAL = 0x21
  };

  enum class Feature_Selector
  {
    ENDPOINT_STALL,
    DEVICE_REMOTE_WAKEUP
  };

  enum class PID_Types
  {
    Special = 0b00,
    Token = 0b01,
    Handshake = 0b10,
    Data = 0b11
  };

  enum class Special
  {
    PRE = 0b11
  };

  enum class Token
  {
    OUT = 0b00,
    SOF = 0b01,
    IN = 0b10,
    SETUP = 0b11
  };

  enum class Handshake
  {
    ACK = 0b00,
    NACK = 0b10,
    STALL = 0b11
  };

  enum class Data
  {
    DATA0 = 0b00,
    DATA1 = 0b10
  };

  constexpr uint8_t PID(uint8_t type, uint8_t name)
  {
    return type + (name << 2);
  }

  struct SetupToken
  {
    uint8_t bmRequestType;
    Request bRequest;
    uint16_t wValue;
    uint16_t wIndex;
    uint16_t wLength;
    uint8_t data[];
  };

 public:
  void reset() {}
  void get_descriptor() {}
  void set_address() {}

  Handshake process_interfce_request(SetupToken *req)
  {
    if (req->bRequest == Request::GET_STATUS)
      {
        req->data[0] = 0;
        req->data[1] = 0;
        return Handshake::ACK;
      }
    else
      {
        return Handshake::STALL;
      }
  }
};