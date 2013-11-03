#include <stdio.h>
#include <time.h>


int main(int argc, char const *argv[])
{
	/*time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	int anio = tm.tm_year + 1900;
	int mes  = tm.tm_mon + 1;
	int dia  = tm.tm_mday;
	int hora = tm.tm_hour;
	int min  = tm.tm_min;
	int sec  = tm.tm_sec;

	printf("%d-%d-%d %d:%d:%d\n", dia, mes, anio, hora, min, sec);	*/

	int cien = 7;
	int diez = 10;
	int tres = 3;

	int x1 = cien / 100;
	printf("1 - %d\n", x1);

	int nuevo = cien - 100*x1;
	int x2 = nuevo / 10;
	printf("2 - %d\n", x2);

	nuevo = nuevo - 10*x2;
	int x3 = nuevo;
	printf("3 - %d\n", x3);

	return 0;
}

