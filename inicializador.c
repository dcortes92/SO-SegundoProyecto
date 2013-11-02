#include "librerias.h"


int main()
{
    char c;
    int shmid;
    key_t key;
    char *shm, *s;

    /* Se llamará 1234 al segmento de memoria compartida */
    key = 1234;

    int num_lineas = 10;
    int tamanio_mem = num_lineas*30 + 1;
    
    /* Se crea el segmento */
    if ((shmid = shmget(key, tamanio_mem, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        return -1;
    }

    /* Se adjunta el segmento al espacio de datos */
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        return -1;
    }

    /* Se insertan datos a la memoria para que los otros procesos lo lean */
    s = shm;

    int i;
    for (i = 0; i < tamanio_mem; i++)
        *s++ = 'X';

    return 1;
}
