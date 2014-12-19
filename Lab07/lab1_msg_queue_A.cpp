#include <stdio.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>

#define MSG_MAX 256

struct message
{
    long int message_type;
    char msg[MSG_MAX];
};

int main(int argc, char const *argv[])
{
    key_t k = 0x12345;
    int msgid = msgget(k,IPC_CREAT | 0666);
    printf("[A] Msg Queue id: %d\n",msgid);

    message m;
    m.message_type = 1;
    printf("Please input:");
    while( *(gets(m.msg)) != 'e'){

        if (msgsnd(msgid,(const void *)&m,sizeof(m) - sizeof(long int),0))
        {
            printf("Error!\n");
            return 0;
        }

        printf("Seneded!\n");
        printf("Please input:");
    }

    msgsnd(msgid,(const void *)&m,sizeof(m) - sizeof(long int),0);

    return 0;
}
