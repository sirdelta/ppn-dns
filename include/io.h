/**
 * @file io.h
 * 
 * @brief I/O operations.
 * 
 * @author @besnardjb, https://github.com/besnardjb
 */
#ifndef IO__H
#define IO__H

#include "settings.h"
#include <stdio.h>

/**
 * @brief Write some bytes from a buffer into a file referred by
 * a file descriptor.
 */
ssize_t safe_write(int fd, void *buf, size_t size);

/**
 * @brief Read some bytes from a file descriptor into a buffer.
 */
ssize_t safe_read(int fd, void *buf, size_t size);

#endif  //IO__H
