#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

long long int count = 0;

void* routine(void* i){
    for (int i = 0; i < 250000; ++i)
        count++;
    printf("Thread %d | Thread ID: %lu\n",*((int*) i), (pthread_self()));
    return (void*) new int(0);
}

int main(int argc, char const *argv[])
{
    pthread_t* thread = new pthread_t[4];
    for (int i = 0; i < 4; ++i)
        if(pthread_create(thread+i,NULL,routine,(void *) new int(i)))
            printf("GG\n");
    
    for (int i = 0; i < 4; ++i)
        if(pthread_join(*(thread+i),NULL))
            printf("GGG\n");

    printf("count = %lld\n", count);

    return 0;
}
