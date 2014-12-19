#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char const *argv[])
{
    int pid = fork();

    if(pid == 0){
        printf("This is child process, PID = %d\n", getpid());
        int i = 0;
        while(true){
            printf("\n\033[1A[Child Process] looping < %d >",i++);
        }
    }
    
    printf("Press any key to use system call to kill the child process...\n");
    getchar();
    kill(pid,SIGTERM);
    printf("\nChild process killed\n");
    return 0;
}
