#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

int main(){
  char src[256], dst[256];
  printf("Source file path: ");
  scanf("%255s", src);
  printf("Destination file path: ");
  scanf("%255s", dst);
  printf("src: %s, dst: %s\n", src, dst);
  int src_fd = open(src, O_RDONLY);
  if(src_fd < 0){
    perror("open of source file failed");
    exit(1);
  }
  int dst_fd = open(dst, O_WRONLY|O_CREAT|O_TRUNC, 0644);
  if(dst_fd < 0){
    perror("open of destination file failed");
    exit(1);
  }
  char buf[4096];
  int bytes_read = 0;
  int bytes_written = 0;
  int total_bytes = 0;
  while((bytes_read = read(src_fd, buf, 4096)) > 0){
    bytes_written = write(dst_fd, buf, bytes_read);
    if (bytes_written != bytes_read){
      perror("Write failed");
      exit(1);  
    }
    total_bytes += bytes_written;
  }
  printf("total bytes read: %d\n", total_bytes);
  close(src_fd);
  close(dst_fd);
}

