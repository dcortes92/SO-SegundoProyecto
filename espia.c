#include "librerias.h"

/* Estado de la memoria compartida, imprime todo */
int estadoMemoria();

int estadoProcesos();

int cantidad_procesos();

int cantidad_lineas();

void main()
{
	int option;
	int loop = 1;
	
	while(loop)
	{
		printf("*** Espia ***\n\n");
		printf("0. Estado de la memoria\n1. Estado de los procesos\n2. Salir");
		printf("\n\n");
		
		scanf("%d", &option);
		
		switch(option)
		{
			case 0:
				printf("Estado de la memoria\n");
				estadoMemoria();
			break;
			
			case 1:
				printf(" ****** Estado de los procesos ******\n");
				estadoProcesos();
			break;
			
			case 2:
				loop = 0;
			break;
			
			default:
				printf("Opcion incorrecta\a");
			break;			
			
		}		
	}
}

int estadoMemoria()
{
	int shmid;
    key_t key;
    char *shm, *s;
    /*
    * Obtenemos el segmento de memoria llamado
    * "1234", creado por inicializador.
    */
    key = 1234;

    int num_lineas = cantidad_lineas();
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
    
    /* Se imprime el contenido de la memoria en formato entendible */
    int contador = 0;     
    char linea[30];
    int i;
    for (s = shm + 1; *s != '\0'; s++)
    {
		if(contador == 30)
		{
			for (i = 0; i < 30; i++)
			{
				putchar(linea[i]);
			}
			printf("\n");
			contador = 0;
		}
		else
		{
		 	linea[contador] = *s;    
	    	contador++;
		}        
    }
}

int estadoProcesos()
{
	int shmid;
    key_t key;
    char *shm, *s;
    /*
    * Obtenemos el segmento de memoria llamado
    * "5678", creado por inicializador.
    */
    key = 5678;

    int num_lineas = cantidad_procesos(); //se lee el archivo con la cantidad de procesos en ejecución.
    int tamanio_mem = num_lineas*10 + 2;
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
    
    printf("\n PID\tTipo\tEstado\tUsando memoria\n");
    /* Se imprime el contenido de la memoria en formato entendible */
    int contador = 0;     
    char linea[10];
    int i;
    printf(" ");
    for (s = shm + 1; *s != '\0'; s++)
    {
		if(contador == 10)
		{
			for (i = 0; i < 10; i++)
			{
				if(i > 3)
				{
					if(linea[i] != ' ')
					{
						printf("\t");
					}
					else
					{
						continue;
					}
				}
				putchar(linea[i]);
			}
			printf("\n");
			contador = 0;
		}
		else
		{
		 	linea[contador] = *s;    
	    	contador++;
		}        
    }
    
    printf(" \n\nTipo: w = writer, r = reader, e = reader egoista\n");
    printf(" Estado: a = activo, b = bloqueado / durmiendo\n");
    printf(" Usando memoria: 1 = usando memoria compartida, 0 = no esta usando memoria compartida\n\n");
}

int cantidad_procesos() 
{
	FILE *fp;
	char buffer[2];

	fp = fopen("cantidadProcesos.txt", "r");
	fscanf(fp, "%s", buffer);
	fclose(fp);
	
	return atoi(buffer);
}

int cantidad_lineas() 
{
	FILE *fp;
	char buffer[2];

	fp = fopen("cantidadLineas.txt", "r");
	fscanf(fp, "%s", buffer);
	fclose(fp);
	
	return atoi(buffer);
}
