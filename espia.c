#include "librerias.h"

/* Estado de la memoria compartida, imprime todo */
void estadoMemoria();

/* Estado de los readers, recibe una bandera en
   caso de que se solicite el estado de los egoistas */
void estadoReaders(int esEgoista);

/* Estado de los writers */
void estadoWriters();

int main()
{
	int option;
	int loop = 1;
	
	while(loop)
	{
		system("clear");
		printf("*** Espia ***\n\n");
		printf("0. Estado de la memoria\n1. Estado de los readers\n2. Estado de los readers egoistas\n3. Estado de los writers\n4. Salir");
		printf("\n\n");
		
		scanf("%d", &option);
		
		switch(option)
		{
			case 0:
				printf("Estado de la memoria");
			break;
			
			case 1:
				printf("Estado de los readers");
			break;
			
			case 2:
				printf("Estado de los readers egoistas");
			break;
			
			case 3:
				printf("Estado de los writers");
			break;
			
			case 4:
				loop = 0;
			break;
			
			default:
				printf("Opcion incorrecta\a");
			break;
			
			
		}		
	}
}
