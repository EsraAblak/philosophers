#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char* argv[])
{
    int x = 0;
    int pid = fork();  //iki process oluşturur
    if (pid == -1) {
        return 1;
    }
    // 1. printf("hello world\n");
    // 2. printf("proccess id %d\n",getpid());
    
    // 3.
    if (pid == 0) //child proccess!
        x++;
    sleep(2);
    printf("value of x: %d\n",x);

    if (pid != 0) {
        wait(NULL);
    }
    return 0;
}

/*
    1-> ÇIKTI
    hello world
    hello world

    2-> ÇIKTI
    procces id 1111    -->rakamların farklı olması önemli olan
    procces id 2222         çünkü iki farklı proccess!!

    3-> ÇIKTI
    value of x: 2
    value of x: 3      //ikisinin de  3 olması gerekmez miydi child parent'den dolayı mı ? 
*/