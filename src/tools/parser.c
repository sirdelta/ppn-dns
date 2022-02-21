/**
 * @file parser.c
 * 
 * @brief Syntax analysis for validation of stored and exchanged data.
 */
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>

//
int parse_command(const char *cmd)
{
  if (!cmd)
    return 0;

  return 1;
}

//
long int parse_numeric(const char *string)
{
  if (!string)
    return 0;

  char *end;
  errno = 0;

  long int val = strtol(string, &end, 10);

  if (errno || end == string || *end != '\0')
    return 0;

  return val;
}

//
int parse_fqdn(const char *fqdn)
{
  if (!fqdn)
    return 0;
  
  size_t lf = strlen(fqdn);   /* The length of the input domain name. */
  
  /* First, we check the format of the domain name. */

  if (lf >= NAMES_SIZE_LIMIT)
    return 0;

  if (fqdn[lf - 1] != '.')
    return 0;

  /* Now, we check the length of each label in the domain name. */
  
  int count = 0;  /* Count the number of character in a label. */
  
  /* We walk through the string and look for the '.' character each time. */
  for (size_t i = 0; i < lf; i++)
	{
	  if (fqdn[i] == '.')   /* If it is the end of the label... */
    {
      /* Check the length of the current label. */
      if (count == 0 || count > LABELS_SIZE_LIMIT)
        return 0;
      
      count = 0;  /* The counter is reset for the enxt label. */
    }
    else
      count++;    /* We increment the number of character in the label. */
	}
  
  return (int) lf;
}

//
int parse_ipv4_addr(const char *addr)
{
  if (!addr)
    return 0;

  struct in_addr host;   /* Used to store an IPV4 address. */

  return inet_pton(AF_INET, addr, &host);
}

//
int parse_ipv6_addr(const char *addr)
{
  if (!addr)
    return 0;

  struct in6_addr host;  /* Used to store an IPV6 address. */

  return inet_pton(AF_INET6, addr, &host);
}

//
int parse_host_info(const char *info)
{
  if (!info)
    return 0;

  /* First, we check the length of the input information. */

  size_t li = strlen(info);

  if (li >= MACHINE_AND_SYSTEM_NAMES_SIZE_LIMIT)
    return 0;

  /* Then, we check the format. */

  size_t i;  /* Used to count character in a string. */

  for (i = 0; i < li; i++)
  {
    /* Digits. */
    if ((info[i] >= '0' && info[i] <= '7') || info[i] == '8' || info[i] == '9')
      continue;

    /* Alpha. */
    if ((info[i] >= 'A' && info[i] <= 'Z') || (info[i] >= 'a' && info[i] <= 'z'))
      continue;

    /* Special characters. */
    if (info[i] == '-' || info[i] == '/')
      continue;

    break;
  }

  return ( i == li );
}
