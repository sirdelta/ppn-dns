#ifndef IO_H
#define IO_H

#include "proto.h"

#ifdef __cplusplus
extern "C" {
#endif

ssize_t safe_write(int fd, void *buff,  size_t size);
ssize_t safe_read(int fd, void * buff, size_t size);

int send_command(int fd, command_type_t cmd, char * key, char * value);

#ifdef __cplusplus
}
#endif

#endif /* IO_H */
