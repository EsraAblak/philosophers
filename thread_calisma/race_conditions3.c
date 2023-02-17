#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int mails = 0;

void *routine()
{
    for(int i = 0; i < 100000; i++)
        mails++;
    return (NULL);
}

int main()
{
    pthread_t t1,t2;
    if (pthread_create(&t1,NULL,&routine,NULL))
        return(1);
    if (pthread_create(&t2,NULL,&routine,NULL))
        return(2);
    if (pthread_join(t1,NULL))
        return 3;
    if (pthread_join(t2,NULL))  //join finish the execution
        return 4;
    printf("number of mails: %s\n",mails);   
    return 0;
}


/*
    ÇIKTI
    for' da i = 100000 -> number of mails: 200000
    for' da i = 1000000 -> number of mails: 1496943   //RACE CONDITIONS

                    t1      t2      NORMAL ÇALIŞMA DURUMU
    read            23      24
    increment       23      24
    write mails     24      25 

                    t1      t2      HATALI ÇALIŞMA DURUMU
    read            29      23      t2 çalışırken sistem ona kısa süreli dur diyo çünkü t1 işlerini yapması lazım
    increment       29      30          t1 artarken sıra t2 ye geliyor t2 t1'in değerini alıyo ama arttırma kıs-
    write mails     30      24              mında kendi değerini arttırıyor. Bunun sonucunda biz çıktı olarak
                                                hatalı sonuç görüyoruz->DATA RACE!!!!
    t2'deki bu farkın sebebi; t2 tekrar çalışmaya başladığında read değeri 23, increment adımına geldiğinde 
    kendi hafızasında tuttuğu 23 değerini arttırmak yerine cpu register'da olan değeri yani 30'u alır.
    (CPU REGISTER: özel bellek birimleri gibi düşünülebilir (mikroişlemcilerde -> Mikroişlemci(CPU-Central
    Processing Unit)) çeşitli verilerin geçici süreler için saklanması ve bu veriler üzerinde işlem yapılması için 
    register'lardan yararlanır.)
    t2 son işlemde kendi hafızasında tuttuğu arttırılmış değeri yazdırır. yani hatalı çıktı olan.

    neden 1000 gibi sayıda data race olmadı da 1000000'da oldu? çünkü ilk thread routine fonksiyonuna gidip mailsi
    arttırırken daha ikinci thread gelmemiştir bu işlemler çok hızlı gerçekleşir (doğru sonç garantisi vermez).
    ama bir milyon gibi bir sayı verdiğimizde ilk thread işlem yaparken ikinci thread'de oluşur ve fonksiyona gelir
    böylece işlem karışmaya başlar. Bunu önlemek için de mutex kullanılır.

*/