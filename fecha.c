#include <stdio.h>
#include <time.h>


int main(int argc, char const *argv[])
{
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	int anio = tm.tm_year + 1900;
	int mes  = tm.tm_mon + 1;
	int dia  = tm.tm_mday;
	int hora = tm.tm_hour;
	int min  = tm.tm_min;
	int sec  = tm.tm_sec;

	printf("%d-%d-%d %d:%d:%d\n", dia, mes, anio, hora, min, sec);	

	return 0;
}

