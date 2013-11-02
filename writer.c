#include "librerias.h"

/*Parámetros para el Writer, todos son obligatorios.*/

int numberOfWriters; /*Cantidad de procesos writers.*/

int sleepTime; 	 /*Tiempo en que duerme un proceso cuando no está 
				   escribiendo en segundos.*/

int writeTime; 	 /*Tiempo que se le asigna a un proceso para que 
				   escriba en la memoria compartida, segundos*/

//int status;

int main(int argc, char *argv[])
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

				int shmid;
				key_t key;
				char *shm, *s;

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

				while(1)
				{		
					s = 0;			
					if (*s == '0')
					{
						/* Se pide el semáforo */
						*s = '1';
						printf("***** Proceso %d leyendo ******\n\n", getpid());
						
						/* Nombre del segmento de memoria compartida */
						key = 1234;

						int num_lineas = 10;
						int tamanio_mem = num_lineas*30 + 1;
				
						int j = 0;
						char linea[30];
						
						for (s = (shm + 1); *s != NULL; s++)
						{
							if (*s == 'X') 
							{
							    *s = 'R';
							    /*Se escribe la línea*/
							    sleep(writeTime);
							}
							else
							{
								j++;
								s += 30;
							}
						}
						
						/*Se devuelve el semáforo*/
						s = 0;
						*s = '0';
						printf("\n\n");
						sleep(sleepTime);
					}
					else
					{
						sleep(sleepTime);
					}					
				}
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

void agregarCeros(int numeroLinea)
{
	int cantidadLineas = 10;
	int i = 0;
	while(cantidadLineas != 0)
	{
		i++;
		cantidadLineas = cantidadLineas/10;
	}

	int j = 0;
	while(numeroLinea != 0)
	{
		j++;
		numeroLinea = numeroLinea/10;
	}	

	int diferencia = i - j;

	char numero[diferencia];
	for (i = 0; i < diferencia; ++i)
	{
		numero[i] = '0';
	}
}
