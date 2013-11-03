#include "librerias.h"
#include <time.h>

/*Parámetros para el Reader, todos son obligatorios.*/

int numberOfReaders; /*Cantidad de procesos readers.*/

int sleepTime;          /*Tiempo en que duerme un proceso cuando no está
                                 leyendo en segundos.*/

int readTime;          /*Tiempo que se le asigna a un proceso para que
                                 lea en la memoria compartida, segundos */

void imprimir_linea(char *linea);

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
                int tamanio_mem = num_lineas*30 + 1;
                
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

                FILE *file;
                file = fopen("PIDs.txt", "a+");
                fprintf(file, "%d\n", getpid());
                fclose(file);
                
                /* Se imprime el contenido del segmento */
	            while(1)
		        {
		        	/*SE SOLICITA EL SEMAFORO*/
	                s = shm;
	                if (*s == '0')
	                {

	                	*s = '1';

                        int j = 0;
                        char linea[30];
                        
                        for (s = shm + 1; *s != '\0'; s++)
                        {
                            if (j == 30)
                            {
                                j = 0;
                                if(linea[0] != 'X')
                                {
                                	printf("****** Proceso egoista %d leyendo ******\n", getpid());
                                	int i;
									for (i = 0; i < 30; i++)
									{
										if (linea[i] != 'X')
										{
											putchar(linea[i]);
										}
									}

									time_t t = time(NULL);
									struct tm tm = *localtime(&t);
									int mes  = tm.tm_mon + 1;
								    int dia  = tm.tm_mday;
								    int hora = tm.tm_hour;
								    int min  = tm.tm_min;
								    int seg  = tm.tm_sec;

									file = fopen("Bitacora.txt", "a+");
					                fprintf(file, "%d egoista leyendo el %d-%d-2013 %d:%d%d\n", getpid(), dia, mes, hora, min, seg);
					                fclose(file);

									s -= 30;
									for (i = 0; i < 30; i++)
									{
										*s++ = 'X';
									}

									tm = *localtime(&t);
									mes  = tm.tm_mon + 1;
								    dia  = tm.tm_mday;
								    hora = tm.tm_hour;
								    min  = tm.tm_min;
								    seg  = tm.tm_sec;

									file = fopen("Bitacora.txt", "a+");
					                fprintf(file, "%d egoista borrando lectura el %d-%d-2013 %d:%d%d\n", getpid(), dia, mes, hora, min, seg);
					                fclose(file);

									printf("\n\n");
									
									/*Se actualiza el estado del proceso a activo y con acceso a la memoria*/
                                	//actualizar_espia(getpid(), 'e', 'a', 1);
									break;                                 
                                }
                                sleep(readTime);
                            }
                            else
                            {
	                            linea[j] = *s;
	                            j++;
                            }
                        }
                        /*SE LIBERA EL SEMAFORO*/
                        s = shm;
                        *s = '0';
                        printf("\n\n");
                        sleep(sleepTime);
	                }
	                else
	                {
	                	time_t t = time(NULL);
	                	struct tm tm = *localtime(&t);
	                	int mes  = tm.tm_mon + 1;
					    int dia  = tm.tm_mday;
					    int hora = tm.tm_hour;
					    int min  = tm.tm_min;
					    int seg  = tm.tm_sec;

	                	file = fopen("Bitacora.txt", "a+");
		                fprintf(file, "%d egoista bloqueado el %d-%d-2013 %d:%d%d\n", getpid(), dia, mes, hora, min, seg);
		                fclose(file);
		                printf("Zona critica en uso\n\n");
		                /*Se actualiza el estado del proceso a activo y con acceso a la memoria*/
                        //actualizar_espia(getpid(), 'e', 'b', 0);
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


void imprimir_linea(char *linea)
{
	
	printf("\n");
}
