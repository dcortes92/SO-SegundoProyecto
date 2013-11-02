#include "librerias.h"

int main()
{

	int shmid;
	key_t key;
	char *shm;
	
	key = 1234;
	
	int num_lineas = 10;
	int tamanio_mem = num_lineas*30 + 1;
	
	/*Se crea el segmento de memoria*/	
	if ((shmid = shmget(key, tamanio_mem, 0666)) < 0) {
        perror("shmget");
        return -1;
    }

    /*Se adjunta el segmento al espacio de memoria asignado*/
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        return -1;
    }
    
    /*Se quita el segmento del espacio en memoria*/
    if (shmdt(shm) == -1) {
        fprintf(stderr, "shmdt failed\n");
        return -1;
    }

	/*Se libera el segmento*/
    if (shmctl(shmid, IPC_RMID, 0) == -1) {
        fprintf(stderr, "shmctl(IPC_RMID) failed\n");
        return -1;
    }
}
