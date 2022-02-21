/**
 * @file parser.h
 * 
 * @brief Syntax analysis for validation of stored and exchanged data.
 * 
 * @see https://datatracker.ietf.org/doc/html/rfc1035
 * @see https://datatracker.ietf.org/doc/html/rfc1010
 */
#ifndef PARSER__H
#define PARSER__H

#include "parameters.h"

//
// int parse_command(const char *cmd);

/**
 * @brief Parse and convert the input string into a long integer.
 * 
 * @return A long interger if success, 0 otherwise.
 */
long int parse_numeric(const char *string);

/**
 * @brief Parse the format of a fully qualified domain name (FQDN).
 * 
 * @return If it is a valid FQDN, a positive integer is returned.
 * If it is not, 0 is returned.
 */
int parse_fqdn(const char *fqdn);

/**
 * @brief Parse the format of an IPV4 host address.
 * 
 * @return If the IPV4 address is valid, a positive integer is returned.
 * If it is not, a negative or nul value is returned.
 */
int parse_ipv4_addr(const char *addr);

/**
 * @brief Parse the format of an IPV4 host address.
 * 
 * @return If the IPV4 address is valid, a positive integer is returned.
 * If it is not, a negative or nul value is returned.
 */
int parse_ipv6_addr(const char *addr);

/**
 * @brief Parse the format of host information (machine and system names).
 * 
 * @return If mmachine and system names are valid, 1 is returned.
 * If it is not, 0 is returned.
 */
int parse_host_info(const char *data);

#endif  //PARSER__H
