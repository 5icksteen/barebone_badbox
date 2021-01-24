#include <cstddef>
#include <cstdint>

extern "C" void *memset(void *dst, int32_t c, size_t n)
{
  int8_t *q = (int8_t *)dst;
  while (n--)
    {
      *q++ = c;
    }
  return dst;
}
