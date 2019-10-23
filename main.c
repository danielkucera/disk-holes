#include <stdio.h>
#include <fcntl.h>

#define _FILE_OFFSET_BITS 64

int main(int argc, char *argv[]) {

   int fd;
   int i;
   int rb;
   long pos = 0;
   int blk;
   long blksize = 1024*1024*atoi(argv[1]);
   unsigned char *buff = malloc(blksize);

   fd = open("/dev/sda", O_RDONLY);

   do {
     if (!(blk % 100))
	printf("\n%08dMB: ", pos/(1024*1024));
     rb = read(fd, buff, blksize);
     //printf("pos %08d \n", pos);
     pos = rb + pos;
     blk = pos/blksize;
//     printf("read %d bytes, pos %d                 \r", rb, pos/BLOCK);

     for (i=0; i<blksize; i++){
  	   if (buff[i] != '\0'){
		   //printf("not empty block at %d\n", i );
  		   break;
  	   }
     }
     if (i==blksize) {
     	//printf("empty block at %x", ftell(fd) );
//	printf("empty block at %d                   \n", pos/BLOCK );
	printf("_");
     } else {
	printf("X");
     }
   } while (rb == blksize);

   close(fd);

   printf("\nfinished at pos %ld\n", pos);

}
