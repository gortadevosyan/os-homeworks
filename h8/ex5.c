#include "safe_io.h"
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

int main(void) {
  int fd = safe_open("./data/sparse.bin", O_WRONLY | O_CREAT | O_TRUNC, 0644);

  safe_write(fd, "START", 5);
  safe_lseek(fd, 1024 * 1024, SEEK_CUR);
  safe_write(fd, "END", 3);
  close(fd);

  fd = safe_open("./data/sparse.bin", O_RDONLY, 0644);
  long s = safe_lseek(fd, 0, SEEK_END);
  printf("Apparent file size: %ld bytes\n", s);
  close(fd);
  return 0;
}
