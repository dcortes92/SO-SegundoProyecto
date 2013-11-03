#include "librerias.h"
#include <time.h>


/*Parámetros para el Writer, todos son obligatorios.*/

int numberOfWriters; /*Cantidad de procesos writers.*/

int sleepTime;          /*Tiempo en que duerme un proceso cuando no está
                                 escribiendo en segundos.*/

int writeTime;          /*Tiempo que se le asigna a un proceso para que
                                 escriba en la memoria compartida, segundos*/

void procesar_linea(char *s, int numeroLinea);
void procesar_pid(char *s, int pid);
void procesar_fecha(char *s);

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
                
                key = 1234;

                int num_lineas = 10;
                int tamanio_mem = num_lineas*30 + 1;

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
                    s = shm;            
                    if (*s == '0')
                    {
                        /*SE SOLICITA EL SEMAFORO*/
                        *s = '1';
                        printf("El semaforo ya es mio\n");
        
                        int j = 0;
                        char linea[30];
                        
                        for (s = shm + 1; *s != NULL; s++)
                        {
                            if (*s == 'X')
                            {
                                printf("****** Proceso %d escribiendo ******\n\n", getpid());

                                procesar_linea(s, j);                             	

                                procesar_pid(s, getpid());

                                procesar_fecha(s);

                             	sleep(writeTime);
                                break;
                            }
                            else
                            {
                                j++;
                                s += 30;
                            }
                        }
                        /*SE LIBERA EL SEMAFORO*/
                        s = shm;
                        *s = '0';
                        printf("El semaforo ya es libre\n");
                        printf("\n\n");
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

void procesar_linea(char *s, int numeroLinea)
{
    int x1 = numeroLinea / 100;

    int nuevo = numeroLinea - 100*x1;
    int x2 = nuevo / 10;

    nuevo = nuevo - 10*x2;
    int x3 = nuevo;

    *s++ = '#';
    *s++ = x1 + 48;
    *s++ = x2 + 48;
    *s++ = x3 + 48;
    *s++ = '.';
    *s++ = ' ';
}

void procesar_pid(char *s, int pid)
{
    int x1 = pid / 1000;
    int xn1 = pid - 1000*x1;

    int x2 = xn1 / 100;
    int xn2 = xn1 - 100*x2;

    int x3 = xn2 / 10;
    int xn3 = xn2 - 10*x3;
    
    int x4 = xn3;

    *s++ = x1 + 48;
    *s++ = x2 + 48;
    *s++ = x3 + 48;
    *s++ = x4 + 48;
    *s++ = ' ';
}

void procesar_fecha(char *s)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    int mes  = tm.tm_mon + 1;
    int dia  = tm.tm_mday;
    int hora = tm.tm_hour;
    int min  = tm.tm_min;
    int seg  = tm.tm_sec;


    /*AGREGAR EL DIA*/
    int d1 = dia / 10;
    int d2 = dia - 10*d1;
    *s++ = d1 + 48;
    *s++ = d2 + 48;
    *s++ = '-';

    /*AGREGAR EL MES*/
    int m1 = mes / 10;
    int m2 = mes - 10*m1;
    *s++ = m1 + 48;
    *s++ = m2 + 48;
    *s++ = '-';
    *s++ = '2';
    *s++ = '0';
    *s++ = '1';
    *s++ = '3';
    *s++ = ' ';

    /*AGREGAR EL HORA*/
    int h1 = hora / 10;
    int h2 = hora - 10*m1;
    *s++ = h1 + 48;
    *s++ = h2 + 48;
    *s++ = ':';

    /*AGREGAR EL MIN*/
    int min1 = min / 10;
    int min2 = min - 10*min1;
    *s++ = min1 + 48;
    *s++ = min2 + 48;
    *s++ = ':';

    /*AGREGAR EL SEG*/
    int s1 = seg / 10;
    int s2 = seg - 10*s1;
    *s++ = s1 + 48;
    *s++ = s2 + 48;
    *s++ = ' ';
}
