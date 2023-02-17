#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int mails = 0;
pthread_mutex_t mutex; //adım 1 -> mutexini tanımla

void *routine()
{
    for(int i = 0; i < 1000000; i++)
    {
        pthread_mutex_lock(&mutex); // adım 3 -> mutexini kilitle
        mails++;
        pthread_mutex_unlock(&mutex); // adım 4 -> mutexinin kilidini aç
    }
    return (NULL);
}

int main()
{
    pthread_t th[4];
    pthread_mutex_init(&mutex,NULL); // adım 2 -> mutexini başlat
    for(int i = 0; i < 4; i++)
    {
        if (pthread_create(th + i,NULL,&routine,NULL))
            return(1);
        if (pthread_join(th[i],NULL))
            return 2;
    }
    pthread_mutex_destroy(&mutex) // adım 5 -> mutexini kaldır
    printf("number of mails: %s\n",mails);   
    return 0;
}

/*
    ÇIKTI
    number of mails: 4000000 
    MUTEX ile doğru sonuca ulaşılır! 
    mutex aslında kodu korur. kime karşı ? aynı anda çalışan thread'lere karşı.
*/