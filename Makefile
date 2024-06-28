# Target p1
p1: proyecto1.c 
	gcc proyecto1.c -o exe `pkg-config --cflags --libs gtk+-3.0` 
	./exe # Se ejecuta parte 1 del proyecto 
	
clean:
	rm -f exe # Se remueven los ejecutables .exe





p2: proyecto2.c
	# A la par del target se ubican los archivos necesarios.
	gcc proyecto2.c # Se compila el programa.
	./a.out # Se ejecuta el programa.
	
	
