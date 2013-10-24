#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define SHMSZ     27

main()
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

    int num_lineas = 10;
    int caracteres_linea = 2;
    int tamanio_mem = num_lineas*(26+caracteres_linea);
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

    /*
     * Now read what the server put in the memory.
     */
    //s = shm;
    
    int j = 0;
    
    for (s = shm; *s != NULL; s++)
    {
        if (j == 28)
        {
            j = 0;
            printf("\n");
        }
        putchar(*s);
        j++;
    }
    printf("\n");

    

    s = shm;
    s += 28 * 4;
    int i;
    for (i = 0; i < 28; i++)
        *s++ = 'H';
  
    for (s = shm; *s != NULL; s++)
    {
        if (j == 28)
        {
            j = 0;
            printf("\n");
        }
        putchar(*s);
        j++;
    }
    printf("\n");

    if (shmdt(shm) == -1) {
        fprintf(stderr, "shmdt failed\n");
        return -1;
    }

    if (shmctl(shmid, IPC_RMID, 0) == -1) {
        fprintf(stderr, "shmctl(IPC_RMID) failed\n");
        return -1;
    }

    return 0;
}
