#include "librerias.h"

int main()
{

    int shmid;
    key_t key;
    char *shm;
    
    /*
    * Obtenemos el segmento llamado
    * "1234", creado por el inicializador.
    */
    key = 1234;
    
    int num_lineas = 10;
    int tamanio_mem = num_lineas*30 + 1;
    
    if ((shmid = shmget(key, tamanio_mem, 0666)) < 0) {
		perror("shmget");
		return -1;
	}

	/*
    * Se localiza el segmento.
    */
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        return -1;
    }
 
 	/*
 	* Se quita el segmento del espacio de datos en memoria
 	*/   
    if (shmdt(shm) == -1) {
        fprintf(stderr, "shmdt failed\n");
        return -1;
    }

	/*
 	* Se libera el segmento de memoria
 	*/   
    if (shmctl(shmid, IPC_RMID, 0) == -1) {
        fprintf(stderr, "shmctl(IPC_RMID) failed\n");
        return -1;
    }

    FILE *file;
    file = fopen("PIDs.txt", "r");

    char cpid[4];
    while(fscanf(file, "%s", cpid) != EOF)
    {
        int pid = atoi(cpid);
        printf("%d\n", pid);
        kill(pid, SIGTERM);
        kill(pid, SIGKILL);
    }

    fclose(file);

}
