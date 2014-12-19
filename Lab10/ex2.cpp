#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX 5
#define THREAD 3

int queue[MAX];
int head = 0;
int tail = 0;

sem_t* c_lock;
sem_t* p_lock;
sem_t* lock;
void* con(void* a);
void* pro(void* a);

int main(void){
    int i=0;
    pthread_t c[THREAD];
    pthread_t p[THREAD];
    srand(time(NULL));

    c_lock = new sem_t();
    p_lock = new sem_t();
    lock = new sem_t();
    sem_init(c_lock,0,1);
    sem_init(p_lock,0,1);
    sem_init(lock,0,1);

    for (int i = 0; i < 3; ++i)
    {
        pthread_create(c+i,NULL,con,(void *) new int(i));
        pthread_create(p+i,NULL,pro,(void *) new int(i));
    }

    for (int i = 0; i < 3; ++i)
    {
        pthread_join(*(c+i),NULL);
        pthread_join(*(p+i),NULL);
    }

    printf("Program ended!\n");
    return 0;
}

void* pro(void* a){
    for(int i=0;i<3;i++){
        sem_wait(p_lock);
        sem_wait(lock);
        if(tail != ((head+1)%MAX)){
            queue[head] = rand();
            printf("Producer %d has produced value %d at item %d!\nThere are %d items in queue.\n",*((int*) a) + 1,queue[head],head,(head >= tail ? head - tail : head + MAX - tail));
            head = (head+1)%MAX;
        }
        sem_post(lock);
        sem_post(p_lock);

        sleep(1);
    }
    
    pthread_exit(NULL);
}

void* con(void* a){
    for(int i=0;i<3;i++){
        sem_wait(c_lock);
        sem_wait(lock);
        if(tail != head){
            printf("Consumer %d has consumed value %d at item %d!\nThere are %d items in queue.\n",*((int*) a) + 1,queue[tail],tail,(head >= tail ? head - tail : head + MAX - tail));
            tail = (tail+1)%MAX;
        }
        sem_post(lock);
        sem_post(c_lock);

        sleep(1);
    }
    
    pthread_exit(NULL);
}
