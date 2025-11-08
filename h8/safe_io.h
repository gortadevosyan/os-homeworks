#ifndef SAFE_IO
#define SAFE_IO
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int safe_open(const char *path, int flags, mode_t mode); 
ssize_t safe_read(int fd, void *buf, size_t count);
ssize_t safe_write(int fd, const void *buf, size_t count);
off_t safe_lseek(int fd, off_t offset, int whence);
#endif
