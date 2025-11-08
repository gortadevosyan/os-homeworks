#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "safe_io.h"
#include <string.h>
int main(void) {
  char buf[4096];

  int fd = safe_open("./data/numbers.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
  for (int i = 1; i <= 10; i++) {
    int len = snprintf(buf, sizeof(buf), "%d\n", i);
    safe_write(fd, buf, len);
  }
  close(fd);

  fd = safe_open("./data/numbers.txt", O_RDWR, 0);

  int offset = 0;
  int newlines = 0;
  while (safe_read(fd, &buf[0], 1) == 1) {
    if (buf[0] == '\n') newlines++;
    if (newlines == 3) {
      offset = safe_lseek(fd, 0, SEEK_CUR);
      break;
    }
  }
  int line5_offset = offset;
  while (safe_read(fd, &buf[0], 1) == 1) {
    line5_offset++;
    if (buf[0] == '\n') break;
  }
  
  long rem_size = safe_lseek(fd, 0, SEEK_END) - line5_offset;
  safe_lseek(fd, line5_offset, SEEK_SET);
  char remainder[4096];
  if (rem_size > sizeof(remainder)) {
    fprintf(stderr, "Remainder too large for buffer\n");
    close(fd);
    exit(EXIT_FAILURE);
  }
  safe_read(fd, remainder, rem_size);
  
  const char *replacement = "100\n";
  safe_lseek(fd, offset, SEEK_SET);
  safe_write(fd, replacement, strlen(replacement));
  safe_write(fd, remainder, rem_size);

  safe_lseek(fd, 0, SEEK_SET);
  long n;
  printf("Final file content:\n");
  while ((n = safe_read(fd, buf, sizeof(buf))) > 0) {
    safe_write(STDOUT_FILENO, buf, n);
  }

  close(fd);
  return 0;
}
