/**
 * @file alloc.h
 * 
 * @brief Aligned memory allocation.
 * 
 * @see posix_memalign(3), malloc(3)
 */
#ifndef ALLOC__H
#define ALLOC__H

#include "settings.h"
#include <stdio.h>

/* Memory alignement. */

#define ALIGN_SSE    16
#define ALIGN_AVX    32
#define ALIGN_AVX512 64

/**
 * @brief Allocated at least `size` bytes memory and return
 * the address of the allocated memory. The size of the address
 * is a multiple of `align`.
 * @return The allocated memory block address if success,
 * NULL otherwise.
 */
void *mem_aligned_alloc(const size_t align, size_t *size);

#endif  //ALLOC__H
