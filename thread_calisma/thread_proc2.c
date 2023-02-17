#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int x = 2;

void *routine()
{
    // 1. printf("hello from thread\n");
    // 2. printf("proccess id %d\n",getpid());
    // 3. 
    //x++;
    x += 5;
    sleep(2);
    printf("value of x: %d\n",x);
    return (NULL);
}

// 3.
void *routine2()
{
    printf("value of x: %d\n",x);
    return (NULL);
}

int main()
{
    pthread_t t1,t2;
    if (pthread_create(&t1,NULL,&routine,NULL))
        return(1);
    if (pthread_create(&t2,NULL,&routine2,NULL))
        return(2);
    if (pthread_join(t1,NULL))
        return 3;
    if (pthread_join(t2,NULL))
        return 4;
    return 0;
}

/*
    1-> ÇIKTI
    hello from thread
    hello from thread

    2-> ÇIKTI
    proccess id 3333    ikiside aynı id'ye sahip !!
    proccess id 3333

    3-> ÇIKTI
    value of x: 3
    value of x: 3

    value of x: 7   threads are sharing memories!!!!
    value of x: 7
*/