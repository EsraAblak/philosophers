#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int	main(void)
{
	int	a;

	a = 0;
	if (fork() == 0)
	{
		a = a + 5;
		printf("%d, %p\n", a, &a);
	}
	else
	{
		a -= 5;
		printf("%d, %p\n", a, &a);
	}
}

/*
Ebeveyn ve çocuktaki 'a'nın fiziksel adresleri farklı olmalıdır. Ancak programımız sanal adreslere erişir 
(sanal bellek kullanan bir işletim sisteminde çalıştığımızı varsayarsak). Alt süreç,
	üst sürecin tam bir 
kopyasını alır ve 'a'nın sanal adresi alt süreçte değişmez. Bu nedenle,
	hem ebeveynde hem de çocukta aynı
adresleri alırız. 
*/