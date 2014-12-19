#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int* global_var;

void child_process();

int main(int argc, char const *argv[])
{
    int*local_var = new int(10);
    global_var = new int(10);

    printf("main executed...\n");
    pid_t new_pid = fork();
    char* process = (char*) &"main_process";

    if (new_pid == -1)
        printf("Error when forking...\n");
    else if(new_pid == 0){
        process = (char*) &"child_process";
        printf("[%s] local_var = local_var + 10\n",process);
        (*local_var)+=10;
        printf("[%s] global_var = global_var + 10\n",process);
        (*global_var)+=10;
        printf("[%s] Pid = %d, Parent_Pid = %d, global_var = %d, local_var = %d\n",process,getpid(),getppid(),(*global_var),(*local_var));
    }
    else{
        printf("[%s] local_var = local_var + 20\n",process);
        (*local_var)+=20;
        printf("[%s] global_var = global_var + 20\n",process);
        (*global_var)+=20;

        printf("[%s] Waiting for child process...\n",process);
        printf("[%s] Pid = %d, Parent_Pid = %d, global_var = %d, local_var = %d\n",process,getpid(),getppid(),(*global_var),(*local_var));
        wait(NULL);
    }

    return 0;
}

void child_process()
{
    int local_var = 10;
}
