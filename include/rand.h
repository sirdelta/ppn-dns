/**
 * @file rand.h
 * 
 * @brief Uniformly distributed pseudo-random double-precision
 * numbers generator.
 * 
 * @see erand48(3), nrand48(3)
 * @see feature_test_macros(7)
 */
#ifndef RAND__H
#define RAND__H

#ifndef _XOPEN_SOURCE
  #define _XOPEN_SOURCE 700
#endif

#include <stdint.h>

/**
 * @brief Randomly generate an unsigned double-precision floating-point 
 * number using the linear congruential algorithm and 48-bit integer
 * arithmetic.
 * @param seed Used to initialize the 48-bit integer sequence.
 */
double db_rand(const uint16_t seed);

/**
 * @brief Randomly generate an unsigned long integer number using the
 * linear congruential algorithm and 48-bit integer arithmetic.
 * @param seed Used to initialize the 48-bit integer sequence.
 */
long int li_rand(const uint16_t seed);

#endif  //RAND__H
