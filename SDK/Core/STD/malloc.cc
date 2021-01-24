#include <algorithm>
#include <cerrno>
#include <cstddef>
#include <cstdio>
#include <cstdlib>

#if DEBUG
#include <cassert>
#else
#define assert(x) ((void)0)
#endif

extern "C" caddr_t _sbrk_r(int);

constexpr auto ALIGN_TO(auto size, auto align)
{
  return (((size) + (align)-1L) & ~((align)-1L));
}

/* Alignment of allocated block */
constexpr auto MALLOC_ALIGN = (8U);
constexpr auto CHUNK_ALIGN = (sizeof(void *));
constexpr auto MALLOC_PADDING = ((std::max(MALLOC_ALIGN, CHUNK_ALIGN)) - CHUNK_ALIGN);

/* as well as the minimal allocation size
 * to hold a free pointer */
constexpr auto MALLOC_MINSIZE = (sizeof(void *));
constexpr auto MALLOC_PAGE_ALIGN = (0x1000);
constexpr auto MAX_ALLOC_SIZE = (0x80000000U);

using malloc_size_t = size_t;

struct chunk
{
  long size;
  chunk *next;
} malloc_chunk;

const auto CHUNK_OFFSET = sizeof(malloc_chunk.next);
// const auto CHUNK_OFFSET = ((malloc_size_t)(&(((chunk *)0)->next)));

constexpr auto MALLOC_MINCHUNK = (CHUNK_OFFSET + MALLOC_PADDING + MALLOC_MINSIZE);

extern "C" void *malloc(malloc_size_t);
extern "C" void free(void *free_p);

static inline chunk *get_chunk_from_ptr(void *ptr)
{
  chunk *c = (chunk *)((char *)ptr - CHUNK_OFFSET);
  if (c->size < 0) c = (chunk *)((char *)c + c->size);
  return c;
}

chunk *free_list = NULL;
char *sbrk_start = NULL;

static void *sbrk_aligned(malloc_size_t s)
{
  char *p, *align_p;

  if (sbrk_start == NULL) sbrk_start = _sbrk_r(0);

  p = _sbrk_r(s);

  if (p == (void *)-1)
    return p;

  align_p = (char *)ALIGN_TO((unsigned long)p, CHUNK_ALIGN);
  if (align_p != p)
    {
      p = _sbrk_r(align_p - p);
      if (p == (void *)-1)
        return p;
    }
  return align_p;
}

void *malloc(malloc_size_t s)
{
  chunk *p, *r;
  char *ptr, *align_ptr;
  int offset;
  malloc_size_t alloc_size;
  alloc_size = ALIGN_TO(s, CHUNK_ALIGN);
  alloc_size += MALLOC_PADDING;
  alloc_size += CHUNK_OFFSET;
  alloc_size = std::max(alloc_size, MALLOC_MINCHUNK);
  if (alloc_size >= MAX_ALLOC_SIZE || alloc_size < s)
    {
      return NULL;
    }
  p = free_list;
  r = p;
  while (r)
    {
      int rem = r->size - alloc_size;
      if (rem >= 0)
        {
          if (rem >= (int)MALLOC_MINCHUNK)
            {
              r->size = rem;
              r = (chunk *)((char *)r + rem);
              r->size = alloc_size;
            }
          else if (p == r)
            {
              free_list = r->next;
            }
          else
            {
              p->next = r->next;
            }
          break;
        }
      p = r;
      r = r->next;
    }

  if (r == NULL)
    {
      r = (chunk *)sbrk_aligned(alloc_size);

      if (r == (void *)-1)
        {
          return NULL;
        }
      r->size = alloc_size;
    }

  ptr = (char *)r + CHUNK_OFFSET;

  align_ptr = (char *)ALIGN_TO((unsigned long)ptr, MALLOC_ALIGN);
  offset = align_ptr - ptr;

  if (offset)
    {
      *(long *)((char *)r + offset) = -offset;
    }

  assert(align_ptr + size <= (char *)r + alloc_size);
  return align_ptr;
}

extern "C" void free(void *free_p)
{
  chunk *p_to_free;
  chunk *p, *q;

  if (free_p == NULL) return;

  p_to_free = get_chunk_from_ptr(free_p);

  if (free_list == NULL)
    {
      p_to_free->next = free_list;
      free_list = p_to_free;
      return;
    }

  if (p_to_free < free_list)
    {
      if ((char *)p_to_free + p_to_free->size == (char *)free_list)
        {
          p_to_free->size += free_list->size;
          p_to_free->next = free_list->next;
        }
      else
        {
          p_to_free->next = free_list;
        }
      free_list = p_to_free;
      return;
    }

  q = free_list;
  do {
      p = q;
      q = q->next;
    }
  while (q && q <= p_to_free);

  if ((char *)p + p->size == (char *)p_to_free)
    {
      p->size += p_to_free->size;
      if ((char *)p + p->size == (char *)q)
        {
          p->size += q->size;
          p->next = q->next;
        }
    }
  else if ((char *)p_to_free + p_to_free->size == (char *)q)
    {
      p_to_free->size += q->size;
      p_to_free->next = q->next;
      p->next = p_to_free;
    }
  else
    {
      p_to_free->next = q;
      p->next = p_to_free;
    }
}
