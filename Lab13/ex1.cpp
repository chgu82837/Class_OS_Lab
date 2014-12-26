#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <iostream>
#include <cstdlib>

#define IO_MAX 100

struct flock* file_lock(short type, short whence){
    static struct flock ret;
    ret.l_type = type; // lock type
    ret.l_start = 0;
    ret.l_whence = whence;
    ret.l_len = 0; // EOF
    return &ret;
}

int main(){
    int fd = open("lock.txt", O_RDWR);
    printf("Please select one lock type below:\n(1) Read Lock\n(2) Write Lock\n(3) Dont lock\nYour choise: \n");
    char option;
    option = getchar();
    getchar();
    short type;
    int result = fcntl(fd, F_SETLK, file_lock(type, SEEK_SET));
    switch(option){
        case '1':
            result = fcntl(fd, F_SETLK, file_lock(F_RDLCK, SEEK_SET));
            break;
        case '2':
            result = fcntl(fd, F_SETLK, file_lock(F_WRLCK, SEEK_SET));
            break;
        case '3':
            result = -2;
            goto dont_lock;
            break;
        default:
            printf("Unknown option!\n");
            return 0;
        break;
    }
    
    printf("Lock returned value %d!\n",result);
    dont_lock:

    char ca[IO_MAX];

    printf("Do you want to test reading? [Y/n]\n");
    if(getchar() == 'Y'){
        if(read(fd, ca, IO_MAX)<0)
            printf("Can't read file.\n");
        else
            printf("Read successfully with content:\n=============\n%s=============\n",ca);
    }
    getchar();

    printf("Do you want to test writing? [Y/n]\n");
    if(getchar() == 'Y'){
        srand(time(NULL));
        sprintf(ca,"written value <%d>",rand());
        printf("Testing writing... with appending [%s] into file...\n",ca);
        sprintf(ca,"%s\n",ca);
        if(write(fd, ca, strlen(ca))<0)
            printf("Can't write file.\n");
        else
            printf("write file success!\n");
    }
    getchar();

    if(result == 0){ // It will return 0 if the file is locked successfully!
        printf("Press enter to release...\n");
        fflush(stdin);
        getchar();
        //printf(" \n");
        printf("released!\n");
        fcntl(fd, F_SETLKW, file_lock(F_UNLCK, SEEK_SET));
    }

    return 0;
}
