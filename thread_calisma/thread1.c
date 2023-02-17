#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	*routine(void *str)
{
	printf("test from thread , %s\n", str);
	sleep(3);
	printf("ending thread %s\n", str);
	return (NULL);
}

int	main(void)
{
	pthread_t t1;
	pthread_t t2;
	pthread_create(&t1, NULL, routine, "esra");
	pthread_create(&t2, NULL, routine, "ablak");
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
}

/*
	ÇIKTI
	test from thread /esra 
	test from thread /ablak
	ending thread
	ending thread
*/