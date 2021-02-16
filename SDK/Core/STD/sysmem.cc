#include <sys/stat.h>

#include <cerrno>

extern "C" caddr_t _sbrk_r(int incr)
{
  static char *heap_start = NULL;
  // extern char __heap_end;   /* Defined by the linker */
  extern char __heap_start; /* Defined by the linker */
  // char *heap_end = &__heap_end;
  char *prev_heap_start;
  if (heap_start == NULL)
    {
      heap_start = &__heap_start;
    }
  prev_heap_start = heap_start;
  // if (heap_start + incr > heap_end)
  //   {
  //     /* Heap and stack collision */
  //     return (caddr_t)-1;
  //   }
  heap_start += incr;
  return (caddr_t)prev_heap_start;
}

extern "C" caddr_t _sbrk(int incr)
{
  return _sbrk_r(incr);
}
