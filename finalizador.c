#include "librerias.h"

int main()
{

	int shmid;
	key_t key;
	char *shm;
	
	key = 1234;
	
	int num_lineas = 10;
	int caracteres_linea = 2;
	int tamanio_mem = num_lineas*(26+caracteres_linea);
	
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
    
    if (shmdt(shm) == -1) {
        fprintf(stderr, "shmdt failed\n");
        return -1;
    }

    if (shmctl(shmid, IPC_RMID, 0) == -1) {
        fprintf(stderr, "shmctl(IPC_RMID) failed\n");
        return -1;
    }
}
