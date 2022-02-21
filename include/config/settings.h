/**
 * @file settings.h
 * 
 * @brief Functions and parameters used to trace the execution of
 * the program, to set special functionalities, and to manage errors.
 * */
#ifndef SETTINGS__H
#define SETTINGS__H

#include <stdio.h>
#include <errno.h>

/* Error message handler. */
#define ERROR_HANDLER__(msg, ...) \
({ \
  fprintf(stderr, " %s [!] error: ", __TIME__); \
  fprintf(stderr, msg, ##__VA_ARGS__); \
  fprintf(stderr, "\n see the manual for more details.\n\n"); \
})

#endif  //SETTINGS__H
