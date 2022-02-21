/**
 * @file parameters.h
 * 
 * @brief Size limits, default parameters the list of variables useful
 * for the proper execution of the program.
 * 
 * @see https://datatracker.ietf.org/doc/html/rfc1035
 * @see https://datatracker.ietf.org/doc/html/rfc1010
 * */
#ifndef PARAMETERS__H
#define PARAMETERS__H

#include <stdio.h>
#include <stdint.h>

/* Limits. */

#define NAMES_SIZE_LIMIT    255
#define LABELS_SIZE_LIMIT   63

#define MACHINE_AND_SYSTEM_NAMES_SIZE_LIMIT  40

/* Buffers and data length. */

#define UDP_MESSAGES_MAX_SIZE    512

#define DNS_HEADER_MIN_SIZE      ( 6 * sizeof(uint16_t) )
#define DNS_QUESTION_MIN_SIZE    ( sizeof(uint16_t) )
#define DNS_RR_MIN_SIZE          ( 2 * sizeof(uint16_t) + sizeof(int32_t) )
#define DNS_DATA_BUFFER_LENGTH   512

#define P2I_KEY_BUFFER_LENGTH    255
#define P2I_VALUE_BUFFER_LENGTH  1024

/* Default values. */

/* The header flags of a query: standard query and recursion desired */
#define DEFAULT_QUERY_STANDARD_HEADER_FLAGS   0x0100

/* The header flags of a response: standard reply and no error */
#define DEFAULT_REPLY_STANDARD_HEADER_FLAGS   0x8000

#endif  //PARAMETERS__H
