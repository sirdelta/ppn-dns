/**
 * @file io.c
 * 
 * @brief I/O operations.
 */
#include "io.h"
#include <string.h>
#include <unistd.h>
#include <errno.h>

//
ssize_t safe_write(int fd, void *buf, size_t size)
{
  ssize_t ret    = 0;   /* The total number of bytes written. */
  size_t written = 0;   /* The number of successful bytes written. */

  /* While there are bytes left to write... */
  while ((size - written) != 0)
  {
    errno = 0;
    ret   = write(fd, buf + written, (size - written));

    /* If an error occurs... */
    if (ret < 0)
    {
      /* The operation must continue even if the function is interrupted
         by a signal. */
      if (errno == EINTR)
        continue;

      /* Other errors are not supported. */
      ERROR_HANDLER__("write() failed: %s.", strerror(errno));
      return ret;
    }

    /* The current number of bytes written is updated. */
    written += (size_t) ret;
  }

  return 0;
}

//
ssize_t safe_read(int fd, void *buf, size_t size)
{
  ssize_t ret    = 0;   /* The total number of bytes read. */
  ssize_t offset = 0;   /* Used to fill the buffer. */

  /* While there are bytes left to read... */
  while (size)
  {
    ret = read(fd, buf + offset, size);

    /* If an errors occurs or an end-of-file is reached... */
    if (ret <= 0)
    {
      ERROR_HANDLER__("read() failed: %s.", strerror(errno));
      return ret;
    }

    offset += ret;           /* The buffer's index is updated. */
    size   -= (size_t) ret;  /* The current number of bytes read is updated. */
  }

  return 0;
}
