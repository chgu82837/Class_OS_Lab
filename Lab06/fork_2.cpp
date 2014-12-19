#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char const *argv[])
{

    printf("main executed...\n");
    char* process = (char*) &"main_process (A)";
    if(fork() == 0){
        if(fork() == 0){
            process = (char*) &"child_process (C)";
            printf("[%s] Pid = %d, Parent_Pid = %d\n",process,getpid(),getppid());
            return 0;
        }
        wait(NULL);
        process = (char*) &"child_process (B)";
        printf("[%s] Pid = %d, Parent_Pid = %d\n",process,getpid(),getppid());
        return 0;
    }
    if(fork() == 0){
        process = (char*) &"child_process (D)";
        printf("[%s] Pid = %d, Parent_Pid = %d\n",process,getpid(),getppid());
        return 0;
    }
    if(fork() == 0){
        process = (char*) &"child_process (E)";
        printf("[%s] Pid = %d, Parent_Pid = %d\n",process,getpid(),getppid());
        return 0;
    }
    wait(NULL);
    wait(NULL);
    wait(NULL);

    printf("[%s] Pid = %d, Parent_Pid = %d\n",process,getpid(),getppid());
    return 0;
}
