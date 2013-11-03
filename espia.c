#include "librerias.h"

/* Estado de la memoria compartida, imprime todo */
int estadoMemoria();

/* Estado de los readers, recibe una bandera en
   caso de que se solicite el estado de los egoistas */
int estadoReaders(int esEgoista);

/* Estado de los writers */
int estadoWriters();

void main()
{
	int option;
	int loop = 1;
	
	while(loop)
	{
		printf("*** Espia ***\n\n");
		printf("0. Estado de la memoria\n1. Estado de los readers\n2. Estado de los readers egoistas\n3. Estado de los writers\n4. Salir");
		printf("\n\n");
		
		scanf("%d", &option);
		
		switch(option)
		{
			case 0:
				printf("Estado de la memoria");
				estadoMemoria();
			break;
			
			case 1:
				printf("Estado de los readers");
			break;
			
			case 2:
				printf("Estado de los readers egoistas");
			break;
			
			case 3:
				printf("Estado de los writers");
			break;
			
			case 4:
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
    * We need to get the segment named
    * "5678", created by the server.
    */
    key = 1234;

    int num_lineas = 10;
    int tamanio_mem = num_lineas*30 + 1;
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
    
    printf("\n\n");
    int i;
    for (s = shm; *s != NULL; s++)
    {
    	for (i = 0; i < 30; i++)
		{
			putchar(*s);
		}
		printf("\n");
    }
    
    printf("\n\n");
}

int estadoReaders(int esEgoista)
{
	
}

int estadoWriters()
{
	
}
