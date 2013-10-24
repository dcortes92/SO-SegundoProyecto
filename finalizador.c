#include "librerias.h"

int main()
{

	int shmid;
	key_t key;
	char *shm, *s;

	int *shm1;

	/*
	* We need to get the segment named
	* "5678", created by the server.
	*/
	key = 1234;
	
	
    if (shmdt(shm) == -1) {
        fprintf(stderr, "shmdt failed\n");
        return -1;
    }

    if (shmctl(shmid, IPC_RMID, 0) == -1) {
        fprintf(stderr, "shmctl(IPC_RMID) failed\n");
        return -1;
    }
}
