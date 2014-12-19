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
    msgrcv(msgid,(void *)&m,sizeof(m) - sizeof(long int),0,0);
    while( (*(m.msg) != 'e') ){
        printf("Msg: [%s], type: [%ld]\n", m.msg,m.message_type);
        msgrcv(msgid,(void *)&m,sizeof(m) - sizeof(long int),0,0);
    }

    return 0;
}
