/**
 * @file compress.h
 * 
 * @brief Compression and decompression of DNS message, in accordance
 * with the RFC 1035.
 * 
 * @see https://datatracker.ietf.org/doc/html/rfc1035
 */
#ifndef COMPRESS__H
#define COMPRESS__H

#include <stdint.h>

/**
 * @brief Compress a buffer/packet wich contains serialized data.
 * The input buffer is reallocted if necessary.
 */
uint8_t *compression(uint8_t *pck);

/**
 * @brief Decompress a buffer/packet wich contains serialized data.
 * The input buffer is reallocted if necessary.
 */
uint8_t *decompression(uint8_t *pck);

#endif  //COMPRESS__H
