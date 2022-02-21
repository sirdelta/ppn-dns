/**
 * @file rand.c
 * 
 * @brief Uniformly distributed pseudo-random double-precision
 * numbers generator.
 */
#include "rand.h"
#include <stdlib.h>

/**
 * @brief Return the random id of the next request.
 */
static int generate_id(const uint16_t seed)
{  
  static int id = 0;  /* A static counter. */

  /* We increment the counter and assign it to the seed. */
  return ( seed + id );
}

//
double db_rand(const uint16_t seed)
{
  uint16_t xsubi[3];   /* A sequence of 48-bit integers */

  /* Initialize the pseudo-random numbers generator. */
  xsubi[0] = (uint16_t) generate_id(seed);
  xsubi[1] = 0;
  xsubi[2] = 0;

  /* A random number over the interval [0.0, 1.0[ is returned. */
  return erand48(xsubi);
}

//
long int li_rand(const uint16_t seed)
{
  uint16_t xsubi[3];   /* A sequence of 48-bit integers */

  /* Initialize the pseudo-random numbers generator. */
  xsubi[0] = seed;
  xsubi[1] = 0;
  xsubi[2] = 0;

  /* A random numer over the interval [0, 2^31[ is returned. */
  return nrand48(xsubi);
}
