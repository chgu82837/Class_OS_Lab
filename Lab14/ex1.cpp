#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define FILE_LENGTH 0xFF

int main (int argc,char *argv[]){
    if(argc < 1){
        printf("Usage:\n\tthe_exe <file>\n");
        return 0;
    }

    int fd;
    char input[FILE_LENGTH] = {0};
    void* file_memory;

    fd = open(argv[1],O_RDWR|O_CREAT,S_IRUSR|S_IWUSR);
    /* Open file. */

    printf("File %s opended with returned code %d\n",argv[1],fd);

    /* Create the memory mapping. */

    lseek(fd,1,SEEK_SET);
    write(fd,input,FILE_LENGTH);

    file_memory = mmap(0,FILE_LENGTH,PROT_WRITE,MAP_SHARED,fd,0);

    /* Close fd */
    close(fd);

    printf("File mapped to memory 0x%lX.\n",(unsigned long)file_memory);

    /* Write a character to memory-mapping area. */
    while(1){
        printf("enter any string (exit to exit):\n>> ");
        gets(input);
        if(strcmp(input,"exit") == 0)
            break;

        sprintf((char*)file_memory,"%s\n",input);
        file_memory = (void *)(((unsigned long)file_memory) + strlen(input) + sizeof(char));
        printf("Content [%s] written!\n",input);
    }

    printf("Exiting...\n");
    munmap((char*)file_memory,FILE_LENGTH);
    return 0;
}
