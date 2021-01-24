#pragma once

#include <cstddef>
#include <cstdint>
#include <functional>

#include "SystemTick.h"
#include "common.h"
extern StaticEvent<> system_events;

class FuncHolder
{
 private:
  Callback mode_ = {};

 public:
  FuncHolder(auto &&func)
  {
    add(std::forward<decltype(func)>(func));
    system_events.call([this] { dispatch(); });
  }
  void add(auto &&func)
  {
    mode_ = std::forward<decltype(func)>(func);
  }
  void dispatch()
  {
    mode_();
  }
};
