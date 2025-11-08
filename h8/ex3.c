#include "safe_io.h"
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

int main(){
  char src[256];
  printf("Source file path: ");
  scanf("%255s", src);
  int fd = safe_open(src, O_RDONLY, 0644);
  long s = safe_lseek(fd, 0, SEEK_END);

  for(long i=0; i<=s-1; i++){
    safe_lseek(fd, i, SEEK_SET);
    char buf;
    safe_read(fd, &buf, 1);
    safe_write(STDOUT_FILENO, &buf, 1);
  }
  safe_write(STDOUT_FILENO, "\n", 1);
  close(fd); 
}
