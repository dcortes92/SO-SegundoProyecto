all: inicializador finalizador reader writer

inicializador: inicializador.c
	gcc -o inicializador inicializador.c

finalizador: finalizador.c
	gcc -o finalizador finalizador.c
    
reader: reader.c
	gcc -o reader reader.c
    
writer: writer.c
	gcc -o writer writer.c
