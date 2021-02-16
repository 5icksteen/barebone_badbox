#pragma once

#include <functional>
#include <memory>

// using Callback = void (*)();
using Callback = std::function<void()>;

enum : bool
{
  OFF,
  ON
};