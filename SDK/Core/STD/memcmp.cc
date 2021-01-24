#include <cstddef>
#include <cstdint>

extern "C" int32_t memcmp(const void *s1, const void *s2, size_t n)
{
  const uint8_t *c1 = (uint8_t *)s1, *c2 = (uint8_t *)s2;
  int32_t d = 0;
  while (n--)
    {
      d = (int32_t)*c1++ - (int32_t)*c2++;
      if (d)
        break;
    }
  return d;
}