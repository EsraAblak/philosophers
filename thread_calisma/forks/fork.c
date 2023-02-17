#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int	main(void)
{
	int a;
	
	a= fork();
	if (a > 0)
		printf("ana proccess\n");
	else
		printf("child\n");
	return (0);
}

//Toplam İşlem Sayısı = 2 n