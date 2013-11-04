#include "librerias.h"

void liberar_memoria();
void liberar_memoria_espia();
int cantidad_procesos();

int main()
{

    liberar_memoria();
	liberar_memoria_espia();	

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

	/*Se borran archivos usados durante el proceso*/
	remove("PIDs.txt");
	remove("Bitacora.txt");
}

void liberar_memoria()
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
    	printf("Error creando el segmento para finalizarlo\n");
		perror("shmget");
		return;
	}

	/*
    * Se localiza el segmento.
    */
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
    	printf("Error localizando el segmento para finalizarlo\n");
        perror("shmat");
        return;
    }
 
 	/*
 	* Se quita el segmento del espacio de datos en memoria
 	*/   
    if (shmdt(shm) == -1) {
        fprintf(stderr, "shmdt failed\n");
        return;
    }

	/*
 	* Se libera el segmento de memoria
 	*/   
    if (shmctl(shmid, IPC_RMID, 0) == -1) {
        fprintf(stderr, "shmctl(IPC_RMID) failed\n");
        return;
    }
}


void liberar_memoria_espia()
{
	int shmid;
    key_t key;
    char *shm;
    
    /*
    * Obtenemos el segmento llamado
    * "5678", creado por el inicializador.
    */
    key = 5678;
    
    int num_lineas = cantidad_procesos();
    int tamanio_mem = num_lineas*10 + 2;
    
    if ((shmid = shmget(key, tamanio_mem, 0666)) < 0) {
		printf("Error creando el segmento del espia para finalizarlo\n");
		return;
	}

	/*
    * Se localiza el segmento.
    */
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        printf("Error localizando el segmento del espia para finalizarlo\n");
        return;
    }
 
 	/*
 	* Se quita el segmento del espacio de datos en memoria
 	*/   
    if (shmdt(shm) == -1) {
        fprintf(stderr, "shmdt failed\n");
        return;
    }

	/*
 	* Se libera el segmento de memoria
 	*/   
    if (shmctl(shmid, IPC_RMID, 0) == -1) {
        fprintf(stderr, "shmctl(IPC_RMID) failed\n");
        return;
    }
}


int cantidad_procesos() 
{
	FILE *fp;
	char buffer[2];

	fp = fopen("cantidadProcesos.txt", "r");
	fscanf(fp, "%s", buffer);
	fclose(fp);
	
	return atoi(buffer);
}
