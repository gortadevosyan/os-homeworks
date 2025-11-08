#include "safe_io.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int safe_open(const char *path, int flags, mode_t mode) {
    int fd = open(path, flags, mode);
    if (fd < 0) {
        perror(path);
        exit(EXIT_FAILURE);
    }
    return fd;
}

ssize_t safe_read(int fd, void *buf, size_t count) {
    ssize_t n = read(fd, buf, count);
    if (n < 0) {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }
    return n;
}

ssize_t safe_write(int fd, const void *buf, size_t count) {
    ssize_t n = write(fd, buf, count);
    if (n != (ssize_t)count) {
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }
    return n;
}

off_t safe_lseek(int fd, off_t offset, int whence) {
    off_t pos = lseek(fd, offset, whence);
    if (pos < 0) {
        perror("lseek");
        close(fd);
        exit(EXIT_FAILURE);
    }
    return pos;
}
