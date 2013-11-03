#include "librerias.h"

/* Memoria compartida */
int crearMemoria(void);
/* Memoria compartida del espia */
int crearMemoriaEspia(void);


void main()
{
    crearMemoria();
	//crearMemoriaEspia();
}

int crearMemoria()
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

    int num_lineas = 10;
    int tamanio_mem = num_lineas*30 + 2;
    
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
    for (i = 1; i < tamanio_mem; i++)
        *s++ = 'X';

}

int crearMemoriaEspia() /*Esta memoria sirve para que los demás procesos escriban en ella y el espia sepa que estan haciendo*/
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

    int num_lineas = 10;
    int tamanio_mem = num_lineas*1000 + 2;
    
    /*
	* Se crea el segmento.
	*/
    if ((shmid = shmget(key, tamanio_mem, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        return -1;
    }

    /*
	* Se adjunta el segmento al espacio de memoria de datos
	*/
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        return -1;
    }

    /*
	* Now put some things into the memory for the
	* other process to read.
	*/
    s = shm;
	*s = '0';
	s++;
    int i;
    for (i = 0; i < tamanio_mem; i++)
    	if( i == tamanio_mem)
    		*s++ = '\0';	
    	else
        	*s++ = 'X';
}
