#include <cstddef>
#include <cstdint>

extern "C" void *memcpy(void *dst, const void *src, size_t n)
{
  const int8_t *p = (int8_t *)src;
  int8_t *q = (int8_t *)dst;
  while (n--)
    {
      *q++ = *p++;
    }
  return dst;
}
