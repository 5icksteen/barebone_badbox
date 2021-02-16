#include <cstdint>

#include "cortex_vectors.h"
#include "macro.h"
#include GEN_HEADER(TARGET, _system)
#include GEN_HEADER(TARGET, _vectors)

constexpr size_t NUM_VECTORS = 1U + NUM_CORTEX_VECTORS + NUM_VENDOR_VECTORS;

inline void copy_data_init()
{
  extern uint32_t __data_load, __data_start, __data_end;
  for (auto dst = &__data_start, src = &__data_load; dst < &__data_end;)
    {
      *dst++ = *src++;
    }
}

inline void fill_zero_bss()
{
  extern uint32_t __bss_start, __bss_end;
  for (auto dst = &__bss_start; dst < &__bss_end;)
    {
      *dst++ = 0;
    }
}

inline void call_init_array()
{
  extern void (*__init_array_start[])(), (*__init_array_end[])();
  for (auto array = __init_array_start; array < __init_array_end;)
    {
      (*array)();
      array++;
    }
}

void Default_Handler()
{
  for (;;) {}
}

void Reset_Handler()
{
  system_preinit();
  copy_data_init();
  fill_zero_bss();
  call_init_array();
  system_init();
  extern int main();
  main();
}
