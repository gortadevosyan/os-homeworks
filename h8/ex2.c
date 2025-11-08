#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

int main(){
  int fd = open("data/data.txt", O_WRONLY|O_CREAT|O_TRUNC, 0644);
  if (fd < 0){
    perror("open failed");
    exit(1);
  }
  int wr = write(fd, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 26);
  if (wr < 26){
    perror("write failed");
    exit(1);
  }
  close(fd);

  fd = open("data/data.txt", O_RDWR);
  if (fd < 0){
    perror("open failed");
    exit(1);
  }

  long s = lseek(fd, 0, SEEK_END);
  if (s < 0) {
    perror("lseek failed");
    close(fd);
    exit(1);
  }
  printf("Current file size: %ld bytes\n", (long)s);

  if (ftruncate(fd, 10) < 0) {
      perror("ftruncate failed");
      close(fd);
      exit(1);
  }
  s = lseek(fd, 0, SEEK_END);
  if (s < 0) {
    perror("lseek failed");
    close(fd);
    exit(1);
  }
  printf("Current file size after truncation: %ld bytes\n", (long)s);

  if (lseek(fd, 0, SEEK_SET) < 0) {
      perror("lseek rewind failed");
      close(fd);
      exit(1);
  }


  char buf[64];
  int bytes_read = read(fd, buf, sizeof(buf) - 1);
  if (bytes_read < 0) {
      perror("read failed");
      close(fd);
      exit(1);
  }

  printf("Remaining content: %s \n", buf);
  close(fd);
}
