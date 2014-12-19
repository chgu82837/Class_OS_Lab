#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <iostream>

#define MSG_MAX 256
#define MSG_KEY 0x12345

// bool conti = true;
int msgid,rcv_type,snd_type;

struct message
{
    long int message_type;
    char msg[MSG_MAX];
};

void die(char* msg){
    printf("ERROR: %s\n",msg);
    exit(-1);
}

void* listen(void* i){
    message m;
    while(true)
    {
        msgrcv(msgid,(void *)&m,sizeof(m) - sizeof(long int),rcv_type,0);

        printf("\n[Message type %c] : %s\n",rcv_type,m.msg);

        if (strcmp(m.msg,"exit") == 0)
            break;
    }
    printf("\nListening Thread %d Ended | Thread ID: %lu\n",*((int*) i), (pthread_self()));
    return (void*) new int(0);
}

void* say(void* i){
    message m;
    m.message_type = snd_type;
    while(true)
    {
        printf("Please input to type %c:",snd_type);
        scanf("%s",m.msg);

        if (msgsnd(msgid,(const void *)&m,sizeof(m) - sizeof(long int),0))
            die("saying...");

        if (strcmp(m.msg,"exit") == 0)
            break;
    }
    printf("Saying Thread %d Ended | Thread ID: %lu\n",*((int*) i), (pthread_self()));
    return (void*) new int(0);
}

int main(int argc, char const *argv[])
{

    // printf("%d..\n", argc);

    // printf("%c!!\n", *argv[1]);
    if (argc != 3)
    {
        printf("Usage: lab2 {msg_send_type} {msg_rcv_type}\n");
        exit(-1);
    }
    rcv_type = **(argv+2);
    snd_type = **(argv+1);

    pthread_t* thread = new pthread_t[2];
    msgid = msgget(MSG_KEY,IPC_CREAT | 0666);
    printf("Msg Queue Started\n * key: %X\n * id: %d\n * msg_send_type: %c\n * msg_rcv_type: %c\n",
        MSG_KEY,msgid,snd_type,rcv_type);

    if(pthread_create(thread,NULL,listen,(void *) new int(0)))
        die("creating listen");

    if(pthread_create(thread+1,NULL,say,(void *) new int(1)))
        die("creating saying");

    //while(conti){}

    if(pthread_join(*(thread),NULL))
        die("joining listen");

    if(pthread_join(*(thread+1),NULL))
        die("joining saying");

    return 0;
}
