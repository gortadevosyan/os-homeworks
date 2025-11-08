#include "safe_io.h"
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

int main(){
  int fd = safe_open("./data/log.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
  char buf[4096];
  int nr = safe_read(STDIN_FILENO, buf, sizeof(buf) - 1);
  buf[nr] = '\0';
  if (nr > 0 && buf[nr - 1] == '\n') {
    buf[nr - 1] = '\0';
  } 
  pid_t pid = getpid();
  char log_entry[4096 + 64];
  int len = snprintf(log_entry, sizeof(log_entry), "PID=%d: %s\n", pid, buf);

  int nw = safe_write(fd, log_entry, len);
  int offset = safe_lseek(fd, 0, SEEK_CUR);

  printf("Final file offset after append: %ld\n", (long)offset);

  close(fd);
}
