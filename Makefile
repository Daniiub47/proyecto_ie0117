# Variables para simplificar el Makefile
CC = gcc
CFLAGS = -Wall -g 
LIBS = `pkg-config --libs gtk+3.0`

# Target p1
p1: main.c 
	$(CC) $(CFLAGS) -o exe main.c $(LIBS) # Se compila parte 1 del proyecto 
	./exe # Se ejecuta parte 1 del proyecto 
	
clean:
	rm -f exe # Se remueven los ejecutables .exe





p2: proyecto2.c
	# A la par del target se ubican los archivos necesarios.
	gcc proyecto2.c # Se compila el programa.
	./a.out # Se ejecuta el programa.
	
	
