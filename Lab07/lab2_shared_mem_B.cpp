#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define MSG_MAX 1024
#define MSG_NAME "PastLeo"

int main(int argc, char const *argv[])
{
    int id = shm_open(MSG_NAME,O_RDONLY,0666);
    char* so = (char*) mmap(0,MSG_MAX,PROT_READ,MAP_SHARED,id,0);

    printf("Shared memery content:\n");

    while( *(so) )
        putchar(*(so++));

    printf("\nEnd of shared memery\n");

    return 0;
}
