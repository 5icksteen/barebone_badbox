#pragma once

#include <cstddef>
#include <cstdint>
#include <functional>

#include "common.h"

class FuncHolder
{
 private:
  Callback mode_ = {};

 public:
  FuncHolder(auto &&func)
  {
    add(std::forward<decltype(func)>(func));
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
