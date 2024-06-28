# proyecto_ie0117
El presente repositorio contiene el diseño del juego Tik Tak Toe (Gato) y la solución del programa Error Esperado, el cual obtiene un subdominio de similitud entre dos curvas cuadráticas, donde, tanto sus constantes, como el porcentaje de error, son definidos por el usuario. Los programas forman parte del proyecto final del curso Programación Bajo Plataformas Abiertas.

## Primera Parte del Proyecto: Tic Tac Toe
Esta parte del código corresponde al primer problema presentado en el proyecto final. En esta ocación se debe realizar un juego de gato con interface gráfica (gtk/glade), en donde se presentará primeramente una matriz 3x3 con 9 botones interactivos. Se debe verificar el gane y el empate de los jugadores "X" y "O" de tal forma que se imprima en la misma interface el ganador al igual que si hay un empate. Esta parte fue desarrollada por Carlos Andrés Garreta.

Para poder ejecutar este código es necesario:

Paso 1) Instalar las librerias necesarias para hacer el código funcional, primero realizan un "apt get update" y luego se podrá instalar el paquete con la librería gtk3 con "sudo apt-get install libgtk-3-dev".

Paso 2) Clonar el repositorio (para asegurarse que no se haya realizado ningun cambio se puede hacer un "git pull").

Paso 3) Escribir el comando "make p1".

Paso 4) Una vez terminado el programa, escribir "make clean" para eliminar el ejecutable.

## Segunda Parte del Proyecto: Error Esperado
Esta segunda parte del proyecto final, se obtiene un subdominio de similitud entre dos curvas cuadráticas, donde, tanto sus constantes, como el porcentaje de error, son definidos por el usuario, por lo tanto, se generan gráficas donde se visualizan las curvas y el rango de valores del eje X cartesiano, donde las curvas se distancien relativamente con un porcentaje de error menor al escogido por el usuario. Las gráficas se obtienen por medio de la herramienta de visualización GNUPlot. Esta sección fue desarrollada a totalidad por la estudiante Daniela Ulloa Barboza.

Para poder ejecutar este código es necesario:

Paso 1) Primero se deberá realizar una actualización para no tener conflictos, por lo que en la terminal de Ubuntu, se deberá utilizar el comando "apt get update", para luego instalar la herramienta de visualización GNUPlot con el comando sudo apt install gnuplot.

Paso 2) Clonar el repositorio (para asegurarse que no se haya realizado ningun cambio se puede hacer un "git pull").

Paso 3) Escribir el comando "make p2".

Paso 4) Escribir en terminal la información para resolver el problema y obtener las gráficas.

Paso 5) Cuando ya se termincó de ejecutar el programa, se deben buscar las imágenes creadas con las gráficas: plot.png y plot_zoom.png para poder visualizar los resultados.

Paso 6) Si se desean eliminar todos los archivos generados por la ejecución de los programas, se puede utilizar el target del Makefiile "make clean" y así se volverá a tener los mismos archivos iniciales.

Nota: Todos los archivos de este repositorio debe estar en una misma carpeta cuando se vayan a compilar y ejecutar, ya que sino el Makefile no podrá cumplir su trabajo.
