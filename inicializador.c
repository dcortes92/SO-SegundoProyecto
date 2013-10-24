
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>


int main()
{
    char c;
    int shmid;
    key_t key;
    char *shm, *s;

    /*
     * We'll name our shared memory segment
     * "5678".
     */
    key = 1234;

    int num_lineas = 10;
    int caracteres_linea = 2;
    int tamanio_mem = num_lineas*(26+caracteres_linea);
    /*
     * Create the segment.
     */
    if ((shmid = shmget(key, tamanio_mem, IPC_CREAT | 0666)) < 0) {
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

    /*
     * Now put some things into the memory for the
     * other process to read.
     */
    s = shm;

    int i;
    for (i = 0; i < tamanio_mem; i++)
        *s++ = 'X';

    return 1;
}
