#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define FILE_LENGTH 0xFF

int main (int argc,char *argv[]){
    if(argc < 3){
        printf("Usage:\n\tthe_exe <file> <start> <end>\n");
        return 0;
    }

    int fd,start,end;
    void* file_memory;

    fd = open(argv[1],O_RDWR,S_IRUSR|S_IWUSR);
    sscanf(argv[2],"%d",&start);
    sscanf(argv[3],"%d",&end);

    int length = end - start;

    printf("File %s opended with returned code %d\n",argv[1],fd);

    /* Create the memory mapping. */
    file_memory = mmap(0,FILE_LENGTH,PROT_READ,MAP_SHARED,fd,0);

    /* Close fd */
    close(fd);

    file_memory = (void *)(((unsigned long)file_memory) + start);

    printf("File mapped to memory 0x%lX.\n",(unsigned long)file_memory);
    printf("File content:\n");

    /* Write a character to memory-mapping area. */
    for (int i = 0; i < length; ++i){
        putchar(*((char*)file_memory));
        file_memory = (void *)(((unsigned long)file_memory) + sizeof(char));
    }

    printf("\n=================\n");
    munmap((char*)file_memory,length);
    return 0;
}
