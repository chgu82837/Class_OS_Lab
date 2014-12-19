#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

#define MSG_MAX 1024
#define MSG_NAME "PastLeo"

int main(int argc, char const *argv[])
{
    int id = shm_open(MSG_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(id,MSG_MAX);
    char* so = (char*) mmap(0,MSG_MAX,PROT_WRITE,MAP_SHARED,id,0);

    printf("%d\n", id);

    char* msg = new char[32];
    printf("Please input:");
    while( *(gets(msg)) != 'e'){

        sprintf(so,"%s",msg);
        so += strlen(msg);

        printf("Saved!\n");
        printf("Please input:");
    }

    *so = 0;

    return 0;
}
