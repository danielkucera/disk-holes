#include <stdio.h>
#include <fcntl.h>

#define BLOCK (1024*1024)
#define _FILE_OFFSET_BITS 64

int main() {

   int fd;
   unsigned char buff[BLOCK];
   int i;
   int rb;
   long pos = 0;
   int blk;

   fd = open("/dev/sda", O_RDONLY);

   do {
     if (!(blk % 100))
	printf("\n%08d: ", blk);
     rb = read(fd, buff, BLOCK);
     //printf("pos %08d \n", pos);
     pos = rb + pos;
     blk = pos/BLOCK;
//     printf("read %d bytes, pos %d                 \r", rb, pos/BLOCK);

     for (i=0; i<BLOCK; i++){
  	   if (buff[i] != '\0'){
		   //printf("not empty block at %d\n", i );
  		   break;
  	   }
     }
     if (i==BLOCK) {
     	//printf("empty block at %x", ftell(fd) );
//	printf("empty block at %d                   \n", pos/BLOCK );
	printf("_");
     } else {
	printf("X");
     }
   } while (rb == BLOCK);

   close(fd);

}
