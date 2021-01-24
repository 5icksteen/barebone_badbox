#include <cstddef>
#include <cstdint>

extern "C" void *memmove(void *dst, const void *src, size_t n)
{
  const int8_t *p = (int8_t *)src;
  int8_t *q = (int8_t *)dst;
  if (q < p)
    {
      while (n--)
        {
          *q++ = *p++;
        }
    }
  else
    {
      p += n;
      q += n;
      while (n--)
        {
          *--q = *--p;
        }
    }
  return dst;
}
