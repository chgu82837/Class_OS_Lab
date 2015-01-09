#include <stdio.h>
#include <sys/select.h>
#include <stdio.h>
#include <fcntl.h> // for open(), close(), read()
#include <string.h> // for memset()
#include <sys/select.h> // for FD_*, select()
#include <limits.h> // for PIPE_BUF
#include <unistd.h>

#define PIPE_CNT 2

/*
int select(int maxfdp1, fd_set * readfds, fd_set * writefds,  fd_set * exceptfds, struct timeval * tvptr);

fd_set  tmpset;    create a fd_set 
int FD_ISSET(int fd, fd_set *fdset);            Returns 1 if fd is set, 0 otherwise 
void FD_CLR(int fd, fd_set *fdset);            Clear a single bit in a fdset 
void FD_SET(int fd, fd_set *fdset);            Set a single bit in a set if you are interested in
void FD_ZERO(fd_set *fdset);            An fd_set is set to all zero bits (read, write, except) 
*/

int main(){
    char buffer[PIPE_BUF];
    int fd[PIPE_CNT];
    char fname[10];
    int ready,maxfd = -1;

    for (int i = 0; i < PIPE_CNT; ++i){
        sprintf(fname,"pipe_%d",i);
        fd[i] = open(fname, O_CREAT|O_RDWR|O_NDELAY);
        if(maxfd < fd[i])
            maxfd = fd[i];
    }
    
    fd_set tmpset;
    timeval tv;
    maxfd++;

    for (int i = 0; i < PIPE_CNT; ++i){
        printf("pipe_%d: %d,",i,fd[i]);
    }
    printf("maxfd: %d\n",maxfd);

    try{
        while(1){
            FD_ZERO(&tmpset);
            tv.tv_sec=3;
            tv.tv_usec=0;

            memset(&buffer, 0, sizeof(buffer));
            for (int i = 0; i < PIPE_CNT; ++i)
                FD_SET(fd[i],&tmpset);

            ready = select(maxfd,&tmpset,NULL,NULL,&tv);
            if(ready < 0){ // Failure
                throw "Failure!";
            }
            if(ready == 0){ // Timeout
                printf("Timeout...\n");
                continue;
            }
            for (int i = 0; i < PIPE_CNT; ++i){
                if(FD_ISSET(fd[i],&tmpset)){
                    read(fd[i],&buffer,sizeof(buffer));
                    printf("Device [pipe_%d]: %s",i,buffer);
                    if((buffer[0] == 'e') && (buffer[1] == 'x') && (buffer[2] == 'i') && (buffer[3] == 't')){
                        throw "Exiting...";
                    }
                }
            }
        }
    }catch(const char* e){
        printf("%s\n",e);
    }

    for (int i = 0; i < PIPE_CNT; ++i)
        close(fd[i]);
    return 0;
}
