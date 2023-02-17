#include <stdio.h>
#include <unistd.h>
int	main(void)
{
	fork();
	fork() && fork() || fork();
	fork();
	printf("forked\n");
	return (0);
}

/*
Genel olarak l seviyesindeysek ve fork() koşulsuz olarak çağrılırsa ,
	seviyede ( l+1 ) 2 l işlemimiz olur.
 Bir ikili ağaçtaki ( l+1 ) seviyesindeki maksimum alt düğüm sayısına eşdeğerdir .


Fork dönüş değeri için: 
	-> Başarı durumunda, ebeveynde alt sürecin PID'si döndürülür.
	-> Başarısızlık durumunda, ebeveynde -1 döndürülür,
		alt süre. oluşturulmaz  ve errno.
	Şu sonuca varabiliriz,
		fork() ebeveynde sıfır olmayan bir değer ve çocukta sıfır döndürür.
*/