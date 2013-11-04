#include "librerias.h"

/* Memoria compartida */
int crearMemoria(int cantidadLineas);
/* Memoria compartida del espia */
int crearMemoriaEspia(int cantidadProcesos);

void main(int argc, char *argv[])
{
	/*Se esperan 2 parámetros además del programa a ejecutar
	  para determinar el tamaño de la memoria compartida para
	  el espía y la cantidad de lineas de memoria compartida.*/
	if(argc == 3) 
	{	
		int cantidadProcesos = atoi(argv[2]);
		int cantidadLineas = atoi(argv[1]);
		crearMemoria(cantidadLineas);		
		crearMemoriaEspia(cantidadProcesos);	
	}
	else
	{
		printf("Faltan parámetros para iniciar el programa.\n");
	}
}

int crearMemoria(int cantidadLineas)
{
	char c;
    int shmid;
    key_t key;
    char *shm, *s;

    /*
	* Se nombrará al segmento de memoria compartida
	* "1234".
	*/
    key = 1234;

    int tamanio_mem = cantidadLineas*30 + 2;
    
    /*
	* Se crea el segmento.
	*/
    if ((shmid = shmget(key, tamanio_mem, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        return -1;
    }

    /*
	* Se adjunta el segmento al espacio de memoria de datos.
	*/
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        return -1;
    }

    /*
	* Se ingresan datos al segmento
	* primero se llena con X para indicarle a los demás que
	* la memoria esta vacia 
	*/
    s = shm;
    *s = '0';
    s++;
    int i;
    for (i = 1; i <= tamanio_mem; i++){
        if( i == tamanio_mem)
    		*s++ = '\0';	
    	else
        	*s++ = 'X';
    }
    
    /* Finalmente se guarda en un archivo la cantidad de procesos 
       para que otros puedan saberlo*/
       
    FILE *fp;
	fp=fopen("cantidadLineas.txt", "w");
	fprintf(fp, "%d", cantidadLineas);
	fclose(fp);
}

/*Esta memoria sirve para que los demás procesos escriban en ella y el espia sepa que estan haciendo*/
int crearMemoriaEspia(int cantidadProcesos) 
{
	char c;
    int shmid;
    key_t key;
    char *shm, *s;

    /*
	* Se nombará a esta segmento
	* "5678".
	*/
    key = 5678;

    int tamanio_mem = cantidadProcesos*10 + 2;
    
    /*
	* Se crea el segmento.
	*/
    if ((shmid = shmget(key, tamanio_mem, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        printf("Error creando el segmento de espia\n");
        return -1;
    }

    /*
	* Se adjunta el segmento al espacio de memoria de datos
	*/
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        printf("Error adjuntando el segmento de espia\n");
        return -1;
    }

    /*
	* Se llena la memoria con X para indicar que la memoria está
	* vacía.
	*/
    s = shm;
	*s = '0';
	s++;
    int i;
    for (i = 0; i <= tamanio_mem; i++){
    	if( i == tamanio_mem)
    		*s++ = '\0';	
    	else
        	*s++ = 'X';
    }
    
    /* Finalmente se guarda en un archivo la cantidad de procesos 
       para que otros puedan saberlo*/
       
    FILE *fp;
	fp=fopen("cantidadProcesos.txt", "w");
	fprintf(fp, "%d", cantidadProcesos);
	fclose(fp);
}
