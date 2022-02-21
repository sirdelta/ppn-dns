/**
 * @file alloc.c
 * 
 * @brief Aligned memory allocation.
 */
#include "alloc.h"
#include <stdlib.h>

void *mem_aligned_alloc(const size_t align, size_t *size)
{
  switch (align)
  {
    case ALIGN_SSE:
    case ALIGN_AVX:
    case ALIGN_AVX512:

      /* We adjust the size to be allocated if necessary. */

      if (*size < align)
        *size = align;
      
      size_t r = *size % align;
      if (r)
        *size += (align - r);

      return aligned_alloc(align, *size);

    default:
      ERROR_HANDLER__("'%lu' not allowed for memory alignement.", align);
      return NULL;
  }
}
