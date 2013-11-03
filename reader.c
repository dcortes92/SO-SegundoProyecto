#include "librerias.h"

/*Parámetros para el Reader, todos son obligatorios.*/

int numberOfReaders; /*Cantidad de procesos readers.*/

int sleepTime;          /*Tiempo en que duerme un proceso cuando no está
                                 leyendo en segundos.*/

int readTime;          /*Tiempo que se le asigna a un proceso para que
                                 lea en la memoria compartida, segundos */

//int status;

int main(int argc, char *argv[])
{
	/*Se esperan 3 parámetros además el del programa a ejecutar*/
	if (argc == 4)
	{
		numberOfReaders = atoi(argv[1]);
		sleepTime = atoi(argv[2]);
		readTime = atoi(argv[3]);
		
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
                int shmid;
                key_t key;
                char *shm, *s;
                /*
                * Obtenemos el segmento llamado
                * "1234", creado por el inicializador.
                */
                key = 1234;

                int num_lineas = 10;
                int tamanio_mem = num_lineas*30 + 2;
                
                /*
                * Se localiza el segmento.
                */
                if ((shmid = shmget(key, tamanio_mem, 0666)) < 0) {
                	perror("shmget");
                	return -1;
                }

                /*
                * Se adjunta el segmento al espacio de datos en memoria.
                */
                if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
                 perror("shmat");
                 return -1;
                }

				/* Se imprime el contenido del segmento */
	            while(1)
		        {
	                s = shm;
	                if (*s == '0')
	                {
                        int j = 0;
                        char linea[30];
                        
                        for (s = shm + 1; *s != '\0'; s++)
                        {
                            if (j == 30)
                            {
                                j = 0;
                                if(linea[0] != 'X')
                                {
                                	printf("****** Proceso %d leyendo ******\n", getpid());
                                	int i;
									for (i = 0; i < 30; i++)
									{
										if (linea[i] != 'X')
										{
											putchar(linea[i]);
										}
									}
									printf("\n\n");                                    
                                }
                                sleep(readTime);
                            }
                            else
                            {
	                            linea[j] = *s;
	                            j++;
                            }
                        }
                        printf("\n\n");
                        sleep(sleepTime);
	                }
		                
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
