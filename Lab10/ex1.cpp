#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int count=0;
sem_t sem;
void* inc(void* a);
void* dec(void* a);

int main(void){
    int i=0;
    pthread_t id[4];

    //sem = new sem_t(0);
    sem_init(&sem,0,1);

    pthread_create(id,NULL,dec,NULL);
    pthread_create(id+1,NULL,inc,NULL);
    pthread_create(id+2,NULL,dec,NULL);
    pthread_create(id+3,NULL,inc,NULL);
    for(i=0;i<4;i++){
        pthread_join(id[i],NULL);   
    }
    printf("\noutput is %d\n",count);
    pthread_exit(NULL);
}

void* inc(void* a){
    int i=0;
    sem_wdait(&sem);
    printf("inc...");
    for(i=0;i<25000000;i++){
        
        count++;
        
    }
    printf(" done \n");
    sem_post(&sem);
    pthread_exit(NULL);
}

void* dec(void* a){
    int i=0;
    sem_wait(&sem);
    printf("dec...");
    for(i=0;i<25000000;i++){
        
        count--;
        
    }
    printf(" done \n");
    sem_post(&sem);
    pthread_exit(NULL);
}
