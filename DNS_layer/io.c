
#include "io.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

ssize_t safe_write(int fd, void *buff,  size_t size)
{
	size_t written = 0;
	while( (size - written) != 0 )
	{
		errno = 0;
		ssize_t ret = write(fd, buff + written, size-written);

		if( ret < 0 )
		{
			if(errno == EINTR)
			{
				continue;
			}

			perror("write");
			return ret;
		}

		written += ret;
	}

	return 0;
}


ssize_t safe_read(int fd, void * buff, size_t size)
{
	int off = 0;

	while(size)
	{
		int ret = read(fd, buff + off, size);

		if( ret < 0)
		{
			return -1;
		}

		if( ret == 0 )
		{
			return -1;
		}

		off+=ret;
		size -= ret;
	}

	return 0;
}

int send_command(int fd, command_type_t cmd_type, char * key, char * value)
{
    command_t cmd;
    cmd.type = cmd_type;
    snprintf(cmd.key, 512, key);
    snprintf(cmd.value, 512, value);


    return safe_write(fd, &cmd, sizeof(command_t));
}