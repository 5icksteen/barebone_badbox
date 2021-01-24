#include "cortex_vectors.h"
#include "target.h"
#include "vendor_vectors.h"

inline void copy_data_init()
{
  extern unsigned __data_load, __data_start, __data_end;
  for (auto dst = &__data_start, src = &__data_load; dst < &__data_end;)
    {
      *dst++ = *src++;
    }
}

inline void fill_zero_bss()
{
  extern unsigned __bss_start, __bss_end;
  for (auto dst = &__bss_start; dst < &__bss_end;)
    {
      *dst++ = 0;
    }
}

// inline void call_preinit_array() {
//     extern void (*__preinit_array_start[])(), (*__preinit_array_end[])();
//     for (auto array = __preinit_array_start; array < __preinit_array_end;) {
//         (*array)();
//         array++;
//     }
// }

inline void call_init_array()
{
  extern void (*__init_array_start[])(), (*__init_array_end[])();
  for (auto array = __init_array_start; array < __init_array_end;)
    {
      (*array)();
      array++;
    }
}

// inline void call_fini_array() {
//     extern void (*__fini_array_start[])(), (*__fini_array_end[])();
//     for (auto array = __fini_array_start; array < __fini_array_end;) {
//         (*array)();
//         array++;
//     }
// }

void Default_Handler()
{
  for (;;) {}
}

void Reset_Handler()
{
  // __disable_irq();
  __Enable_FPU();
  copy_data_init();
  fill_zero_bss();
  // call_preinit_array();
  call_init_array();
  extern void system_init();
  system_init();
  extern void clock_init();
  clock_init();
  // __enable_irq();
  extern int main();
  main();
  // call_fini_array();
  // Default_Handler();
}
