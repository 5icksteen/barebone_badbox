#pragma once

#include <cstddef>
#include <cstdint>
#include <functional>
#include <vector>

class StaticEvent
{
 private:
  std::vector<std::function<void()>> _queue;

 public:
  void call(auto&& events)
  {
    _queue.push_back(std::forward<decltype(events)>(events));
  }

  void dispatch()
  {
    for (const auto& e : _queue) { e(); }
  }
};
