#pragma once

#include <cstddef>

namespace bad
{
template <int StartN, int StartValue = 0, int Step = 1>
class counter
{
  template <int N>
  struct slot
  {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-template-friend"
    friend constexpr auto slot_value(slot<N>);
#pragma GCC diagnostic pop
  };

  template <int N, int I>
  struct writer
  {
    friend constexpr auto slot_value(slot<N>) { return I; }
    static constexpr int  value = I;
  };

  template <int N, typename = decltype(slot_value(slot<N>()))>
  static constexpr int reader(int, slot<N>, int R = slot_value(slot<N>()))
  {
    return R;
  }

  static_assert(sizeof(writer<StartN, StartValue - Step>), "Base case");

  template <int N>
  static constexpr int reader(float, slot<N>, int R = reader(0, slot<N - 1>()))
  {
    return R;
  }

 public:
  template <int N>
  static constexpr int next(int R = writer<N, reader(0, slot<N - 1>()) + Step>::value)
  {
    return R;
  }
};
}  // namespace bad

