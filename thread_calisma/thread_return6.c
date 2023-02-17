#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void	*roll_dice()
{
	int	value;
	value = (rand() % 6) + 1;
    int *keep = malloc(sizeof(int));
    *keep = value;
    //printf("%d\n",value);
    return keep;
}

int	main(void)
{
    int *res;
	srand(time(NULL));
	pthread_t th;
	pthread_create(&th, NULL, roll_dice, NULL);
	pthread_join(th, (void **)&res);
    printf("Value: %d\n",*res);
    free(res);
}

// join ile return değeri alıyoruz.