#pragma once

#include <cstdint>

#include "macro.h"
#include GEN_HEADER(TARGET, )

extern const size_t NUM_VECTORS;

__STATIC_INLINE uint32_t *NVIC_CopyVector()
{
  uint32_t *vectors = reinterpret_cast<uint32_t *>(SCB->VTOR);
  if (SCB->VTOR == ROM_START)
    {
      uint32_t *old_vectors = vectors;
      vectors = reinterpret_cast<uint32_t *>(RAM_START);
      for (uint32_t i = 0; i < NUM_VECTORS; i++)
        {
          vectors[i] = old_vectors[i];
        }
      SCB->VTOR = RAM_START;
    }
  return vectors;
}

__STATIC_INLINE void NVIC_SetVector(IRQn_Type IRQn, uint32_t vector)
{
  NVIC_CopyVector()[IRQn + NVIC_USER_IRQ_OFFSET] = vector;
}

__STATIC_INLINE uint32_t NVIC_GetVector(IRQn_Type IRQn)
{
  uint32_t *vectors = reinterpret_cast<uint32_t *>(SCB->VTOR);
  return vectors[IRQn + NVIC_USER_IRQ_OFFSET];
}
