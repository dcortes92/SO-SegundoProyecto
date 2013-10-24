#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

/*Parámetros para el Writer, el primer parámetro es obligatorio. En
  caso de que no se especifiquen los otros dos se asumen valores por
  defecto.*/

int numberOfWriters; /*Cantidad de procesos writers.*/

int sleepTime = 100; /*Tiempo en que duerme un proceso cuando no está 
				   escribiendo en milisegundos.*/

int writeTime = 100; /*Tiempo que se le asigna a un proceso para que 
				   escriba en la memoria compartida, milisegundos*/

int main(int argc, char *argv[])
{
	int count = argc;
	printf("The number of arguments passed is %d\n", count);
	
	int c = 0;
	while(c < count)
	{
		printf("The argument [%d] is : [%s]\n", c+1, argv[c]);
		c++;
	}
	
	return 0;
}
