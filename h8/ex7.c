#include "safe_io.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void) {
  char path1[256], path2[256];

  printf("Enter first file path: ");
  if (scanf("%255s", path1) != 1) { perror("Failed to read first file path\n"); exit(1); }

  printf("Enter second file path: ");
  if (scanf("%255s", path2) != 1) { perror("Failed to read second file path\n"); exit(1); }

  int fd1 = safe_open(path1, O_RDONLY, 0);
  int fd2 = safe_open(path2, O_RDONLY, 0);

  unsigned char buf1[4096], buf2[4096];
  int byte_index = 0;

  while (1) {
    long n1 = safe_read(fd1, buf1, 4096);
    long n2 = safe_read(fd2, buf2, 4096);

    if (n1 == 0 && n2 == 0) {
      printf("Files are identical\n");
      close(fd1); close(fd2);
      return 0;
    }

    long min_read = n1 < n2 ? n1 : n2;

    for (long i = 0; i < min_read; i++) {
      if (buf1[i] != buf2[i]) {
        printf("Files differ at byte %ld\n", byte_index + i);
        close(fd1); close(fd2);
        exit(1);
      }
    }

    if (n1 != n2) {
      printf("Files differ at byte %ld\n", byte_index + min_read);
      close(fd1); close(fd2);
      exit(1);
    }

    byte_index += min_read;
  }

  close(fd1);
  close(fd2);
  return 0;
}
