######################################################
## Universidad de Costa Rica.                       ##
## Programación Bajo Plataformas Abiertas - IE0117. ##
## Fecha: 27 de junio de 2024.                      ##
## Creadores: Daniela Ulloa Barboza. B77748.        ##
##            Carlos Andrés Garreta Quesada. C13120.##
######################################################  

# *** Makefile para el proyecto final ***

# El objetivo de este documento es emplear los targets junto con el comando "make" para que el usuario no deba preocuparse por
# insertar en terminal cada comando de manera manual, sino que al escribir "make p1" se ejecuta el programa Tik Tak Toe (Gato),
# y si se escribe "make p2" se ejecuta el programa Error Esperado. Además se agrega otro target para limpiar todos los archivos
# generados durante la ejecuación de alguno de los programas, o ambos, y así volver al punto inicial con solo los archivos
# necesarios para ser compilados y ejecutados, nuevamente.

# Target p1:
p1: proyecto1.c 
	gcc proyecto1.c -o exe `pkg-config --cflags --libs gtk+-3.0` # Se compila la primera parte del proyecto.
	./exe # Se ejecuta parte 1 del proyecto.
	
# Target p2:
p2: proyecto2.c
	# A la par del target se ubican los archivos necesarios.
	gcc proyecto2.c -o exe # Se compila el programa.
	./exe # Se ejecuta el programa.

# Target para limpiar:
clean:
	rm -f exe # Se remueven los ejecutables .exe
	rm -f error.dat # Se eliminan los datos de e(x).
	rm -f funciones.dat # Se eliminan los datos de f(x) y g(x).
	rm -f plot.png # Se elimina la gráfica de dominio total.
	rm -f plot_zoom.png # Se elimina la gráfica con zoom.
	





	
	
