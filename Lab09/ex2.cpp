#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handler1(int a){
    printf("[%d] How are you?\n",a);
}

void handler2(int a){
    printf("[%d] I am fine!\n",a);
}

int status = 0;
void change(int a){
    if(!status){
        signal(SIGINT,handler2);
        alarm(3);
    }
    else{
        signal(SIGINT,SIG_DFL);
    }
    status++;
    printf("[%d] SIGALRM got! changed to handler%d\n",a,status);
}

int main(int argc, char const *argv[])
{
    signal(SIGINT,handler1);
    signal(SIGALRM,change);
    alarm(3);
    while(true){}
    return 0;
}
