#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int mails = 0;
pthread_mutex_t mutex;

void *routine()
{
    for(int i = 0; i < 1000000; i++)
    {
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
    }
    return (NULL);
}

int main()
{
    pthread_t th[4];
    pthread_mutex_init(&mutex,NULL);
    for(int i = 0; i < 4; i++)
    {
        if (pthread_create(th + i,NULL,&routine,NULL) != 0)
            return(1);
        printf("thread %d has started \n", i);
        // if (pthread_join(th[i],NULL) != 0) (durum1)
        //     return 2;
        // printf("thread %d has finished execution\n",i);
    }
    // (durum2)
    for(int i = 0; i < 4; i++) //MUTLTI-THREAD
	{
	    pthread_join(th[i],NULL);
	    printf("thread %d has finished execution\n",i);
	}
    pthread_mutex_destroy(&mutex)
    printf("number of mails: %s\n",mails);   
    return 0;
}

/*
    ÇIKTI
    durum 1: pthread_join, pthread_create ile aynı loop'ta olursa:

    thread 0 has started 
    thread 0 has finished execution
    thread 1 has started 
    thread 1 has finished execution
    thread 2 has started 
    thread 2 has finished execution
    thread 3 has started 
    thread 3 has finished execution
    number of mails:40000000 

    yani hiçbir thread aynı anda çalışmıyor. sebebi şu ilk threadı oluşturup onu joinliyoruz yani çalıştırıyoruz
    sonra sistem pthread_join ile oluşan thread'in bitmesini bekliyor. ancak böyle ikinci thread'ı ve kalanlarını
    oluşturuyor. thread'ler tek tek çalışır. bu da multithread'e girmez! (sonuç: aynı döngüde creat ve join yapma)

    durum 2:
    thread 0 has started 
    thread 1 has started 
    thread 2 has started 
    thread 3 has started 
    thread 0 has finished execution
    thread 1 has finished execution
    thread 2 has finished execution
    thread 3 has finished execution
    number of mails:40000000
    ayrıca buradaki execution çıktısı doğru olmak zorunda değil yani illa ilk birincisi daha 
    sonra ikincisi gibi sırayla kapanmayabilir (hangisi işini önce bitirirse o kapanır). biz böyle yazdırırız.
*/