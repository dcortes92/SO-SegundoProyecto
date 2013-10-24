#include "librerias.h"

/*Parámetros para el Writer, todos son obligatorios.*/

int numberOfWriters; /*Cantidad de procesos writers.*/

int sleepTime; 	 /*Tiempo en que duerme un proceso cuando no está 
				   escribiendo en segundos.*/

int writeTime; 	 /*Tiempo que se le asigna a un proceso para que 
				   escriba en la memoria compartida, segundos*/

//int status;

void main(int argc, char *argv[])
{
	/*Se esperan 3 parámetros además el del programa a ejecutar*/
	if (argc == 4)
	{
		numberOfWriters = atoi(argv[1]);
		sleepTime = atoi(argv[2]);
		writeTime = atoi(argv[3]);
		
		int i;
		pid_t pid;
		for (i = 0; i < numberOfWriters; i++)
		{
			pid = fork();
			if (pid == -1) /*Error*/
			{
				printf("Error creando proceso\n");
				break;
			}
			if (pid == 0) /*Child*/
			{
				printf("Proceso hijo: %d PID: %d\n",i, getpid());
				/*Código del writer*/
				
				break;
				/*Con wait se imprime diferente*/
				//exit(0);
			}
		}
		
		/*for (i = 0; i < numberOfWriters; i++) {
    			pid = wait(&status);
    			printf("Child (pid = %d) exited with status %d.\n", pid, status);
  		}*/
	}
	else
	{
		printf("Faltan parámetros para iniciar el programa.\n");
	}
}