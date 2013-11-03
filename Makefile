all: inicializador finalizador reader readerEgoista writer espia

inicializador: inicializador.c
	gcc -o inicializador inicializador.c

finalizador: finalizador.c
	gcc -o finalizador finalizador.c
    
reader: reader.c
	gcc -o reader reader.c

readerEgoista: readerEgoista.c
	gcc -o readerEgoista readerEgoista.c
    
writer: writer.c
	gcc -o writer writer.c
	
espia: espia.c
	gcc -o espia espia.c
