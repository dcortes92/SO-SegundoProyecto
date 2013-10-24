#include "librerias.h"

/*Parámetros para el Reader, todos son obligatorios.*/

int numberOfReaders; /*Cantidad de procesos readers.*/

int sleepTime; 	 /*Tiempo en que duerme un proceso cuando no está 
				   escribiendo en segundos.*/

int writeTime; 	 /*Tiempo que se le asigna a un proceso para que 
				   escriba en la memoria compartida, segundos */

//int status;

int main(int argc, char *argv[])
{
	/*Se esperan 3 parámetros además el del programa a ejecutar*/
	if (argc == 4)
	{
		numberOfReaders = atoi(argv[1]);
		sleepTime = atoi(argv[2]);
		writeTime = atoi(argv[3]);
		
		int i;
		pid_t pid;
		for (i = 0; i < numberOfReaders; i++)
		{
			pid = fork();
			if (pid == -1) /*Error*/
			{
				printf("Error creando proceso\n");
				break;
			}
			if (pid == 0) /*Child*/
			{
				while(1)
				{
					printf("***** Proceso %d leyendo ******\n\n", getpid());
					int shmid;
					key_t key;
					char *shm, *s;

					int *shm1;

					/*
					* We need to get the segment named
					* "5678", created by the server.
					*/
					key = 1234;

					int num_lineas = 10;
					int caracteres_linea = 2;
					int tamanio_mem = num_lineas*(26+caracteres_linea);
					/*
					* Locate the segment.
					*/
					if ((shmid = shmget(key, tamanio_mem, 0666)) < 0) {
					   perror("shmget");
					   return -1;
					}

					/*
					* Now we attach the segment to our data space.
					*/
					if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
					   perror("shmat");
					   return -1;
					}

					/*
					* Now read what the server put in the memory.
					*/
					//s = shm;
					
					int j = 0;
					
					for (s = shm; *s != NULL; s++)
					{
					   if (j == 28)
					   {
						  j = 0;
						  printf("\n");
					   }
					   putchar(*s);
					   j++;
					}
					printf("\n\n");
				}
				return 0;
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
