/*
********************************************************
*** Universidad de Costa Rica.                       ***
*** Programación Bajo Plataformas Abiertas - IE0117. ***
*** Fecha: 27 de junio de 2024.                      ***
*** Creadora: Daniela Ulloa Barboza. B77748.         ***
********************************************************

*** Proyecto: Error Esperado ***

Descripción: Este código corresponde a la solución de la segunda parte del proyecto final, en este se obtiene
un subdominio de similitud entre dos curvas cuadráticas, donde, tanto sus constantes, como el porcentaje de error,
son definidos por el usuario, por lo tanto, se generan gráficas donde se visualizan las curvas y el rango de valores
del eje X cartesiano, donde las curvas se distancien relativamente con un porcentaje de error menor al escogido por
el usuario. */

// Se importan las bibliotecas: 
#include <stdio.h> // Esta es para el printf.
#include <math.h> // Esta es para las operaciones y funciones matemáticas.
#include <string.h> // Esta es para manejo de strings.
#include <stdlib.h> // Se utiliza para la función system.

// Definición de las funciones:
float funcion1(float *p, float x); // Función para obtener f(x) con respecto a una x.
float funcion2(float *p, float x); // Función para obtener g(x) con respecto a una x.
float error_x(float f, float g); // Función para encontrar el porcentaje de error de la diferencia relativa entre funciones con una x.

// Código main:
int main() {
    //*** CONFIGURACIONES POR ENUNCIADO ***
    
    // Se declara el dominio total a evaluar:
    int xi = -100000; // Valor del eje X inicial.
    int xf = 100000; // Valor del eje X final.
    
    // Se declara el valor de muestreo:
    float muestreo_x = 0.1; // Es el valor de aumento para obtener los múltiples resultados.
    
    //*** FIN DE CONFIGURACIONES POR ENUNCIADO ***

    // Declaración de variables:
    float a, b, c, d, e, f; // Constantes de las funciones.
    float array_cons[6]; // array que va a almacenar todas las constantes para un más fácil manejo.
    float *p_array = array_cons; // Un puntero al primer elemento del array de constantes.
    float error_escogido; // Variable que tendrá el valor del porcentaje de error escogido por el usuario.
    float subdom_i = 0; // Variable que almacena el inicio de un subdominio.
    float subdom_f = 0; // Variable que almacena el final de un subdominio.
    int subdom_in = 0; // Variable para determinar si se está dentro o no de un subdominio.
    char subdominios[1000] = "Subdominios: "; // Esta será la cadena que contenga los sundominios a mostrar en las gráficas.

    // Se generan los mensajes hacia el usuario:
    printf("\n***** Bienvenido al programa: Error Esperado *****\n\n");
    printf("En este programa se mostrará el o los subdominios donde la diferencia relativa entre dos curvas cuadráticas sea menor al error escogido.\n\n");
    
    // Bloque de recepción de datos:
    // Información de f(x):
    printf("La primera función f(x) tiene la forma: a * x^2 + b * x + c\n");
    printf("Por favor agregue la constante a: ");
    scanf("%f", &a);
    printf("Por favor agregue la constante b: ");
    scanf("%f", &b);
    printf("Por favor agregue la constante c: ");
    scanf("%f", &c);
    // Información de g(x):
    printf("La segunda función g(x) tiene la forma: d * x^2 + e * x + f\n");
    printf("Por favor agregue la constante d: ");
    scanf("%f", &d);
    printf("Por favor agregue la constante e: ");
    scanf("%f", &e);
    printf("Por favor agregue la constante f: ");
    scanf("%f", &f);
    
    // Se solicita el porcentaje de error al usuario:
    printf("\nPor favor, ahora ingrese el porcentaje de error deseado (0-100): ");
    scanf("%f", &error_escogido);
    printf("\n");
    
    // Bloque para almacenar las constantes en un solo array por medio del puntero, se aumenta en uno para acceder a la siguiente dirección:
    *p_array = a;
    *(p_array + 1) = b;
    *(p_array + 2) = c;
    *(p_array + 3) = d;
    *(p_array + 4) = e;
    *(p_array + 5) = f;
    
    // Se crean dos archivos para almacenar los datos obtenidos y así poder graficarlos en Gnuplot:
    // Archivo con la información de ambas curvas o funciones:
    FILE *doc_funcs = fopen("funciones.dat", "w"); // Se crea el puntero *doc_funcs para acceder luego y se usa con escritura para crear y sobreescribir.
    // Se asegura de que no falle la creación del documento:
    if (doc_funcs == NULL) { // Caso  en el que el puntero no apunta a ningún lado, se asignó incorrectamente.
        perror("\nError al abrir funciones.dat, necesario para almacenar los datos de las funciones.\n"); // Se imprime mensaje de error.
        return 1; // Se concluye el programa por error ya que return distinto de 0 es un error.
    }
    
    // Archivo con la información de la función de error:
    FILE *doc_error = fopen("error.dat", "w"); // Se crea el puntero *doc_error para acceder luego y se usa con escritura para crear y sobreescribir.
    if (doc_error == NULL) { // Caso  en el que el puntero no apunta a ningún lado, se asignó incorrectamente.
        perror("\nError al abrir error.dat, necesario para almacenar los datos del error.\n"); // Se imprime mensaje de error.
        fclose(doc_funcs);  // Se cierra funciones.dat ya que si se llegó a este punto es porque a funciones.dat sí se accedió correctamente.
        return 1; // Se concluye el programa por error ya que return distinto de 0 es un error.
    }
    
    // Código cíclico para obtener todos los datos de interés:
    for (float x = xi; x <= xf; x += muestreo_x) { // Se realiza todo este proceso desde -100000 hasta 100000 en brincos de 0.1.
        // Se hace el llamado de las funciones, obtención de f(x), g(x) y e(x):
        float fx = funcion1(p_array, x);
        float gx = funcion2(p_array, x);
        // Se obtienen todos los valores para poder graficar ambas curvas en el archivo funciones.dat:
        fprintf(doc_funcs, "%.3f %.3f %.3f\n", x, fx, gx);
        // Se previene el caso en el que f(x) = 0 ya que podría generar una indeterminación:
        if (fx != 0) {
            float ex = error_x(fx, gx);
            // Se encuentran los valores de x f(x) y g(x) que cumplan que ex sea menor o igual que el porcentaje de error del usuario:
            if (ex <= error_escogido) {
                fprintf(doc_error, "%.3f %.3f %.3f\n", x, fx, gx);
            // En este bloque se detectan los subdominios específicos:
                if (!subdom_in) {
                subdom_i = x; // Se define el inicio del subdominio.
                subdom_in = 1; // Se pone en uno para poder realizar el printf y generar el string de los subdominios de las gráficas.
                }
                subdom_f = x; // Se encuentra el final del subdominio.
            } else {
            if (subdom_in) {
                printf("Subdominio con porcentaje de error menor al %.2f%%: [%.3f, %.3f]\n", error_escogido, subdom_i, subdom_f);
                char subdom_temp[100]; // Esta cadena almacena un subdominio temporalmente. 
                sprintf(subdom_temp, "[%.2f, %.2f]", subdom_i, subdom_f); // Se guardan los valores pero convirtiéndose en strings.
                strcat(subdominios, subdom_temp); // Se agrega el string de subdom_temp en la cadena declarada anteriormente.
                subdom_in = 0; // Variable cíclica para capturar correctamente los subdominios.
            }
            }
        }
    }

    if (subdom_in) { // If de soporte en caso de que durante el ciclo no se tomen todos los subdominios.
        printf("Subdominio con porcentaje de error menor al %.2f%%: [%.3f, %.3f]\n", error_escogido, subdom_i, subdom_f);
    }
    
    // Se cierran los archivos al terminar de editarlos:
    fclose(doc_funcs);
    fclose(doc_error);
    
    //*** Bloque de Graficación ***
    
    // Código de graficación #1:
    FILE *gnuplotPipe = popen("gnuplot -persistent", "w"); // Se abre.
    if (gnuplotPipe != NULL) {
        // Configuraciones de principal interés para la gráfica con el dominio total:
        fprintf(gnuplotPipe, "set terminal pngcairo size 800,600\n"); // Tamaño de imagen.
        fprintf(gnuplotPipe, "set output 'plot.png'\n"); // Nombre de imagen y formato.
        fprintf(gnuplotPipe, "set title 'Funciones Cuadráticas'\n"); // Título de la gráfica.
        fprintf(gnuplotPipe, "set xlabel 'Eje X'\n"); // Nombre del eje X.
        fprintf(gnuplotPipe, "set ylabel 'Eje Y'\n"); // Nombre del eje Y.
        fprintf(gnuplotPipe, "set xrange [%d:%d]\n", xi, xf); // Rango determinado por variables iniciales de configuración de enunciado.
        // No se determina un rango del eje Y, para que se ajuste automáticamente.
        // Con esta línea se agrega el texto de los subdominios:
        fprintf(gnuplotPipe, "set label '%s' at graph 0.05, graph 0.95 left font ',9'\n", subdominios); // "graph" indica posición y ',9' el tamaño.
        // Con estas líneas se agregan las curvas f(x), g(x) y e(x) con sus leyendas:
        fprintf(gnuplotPipe, "plot 'funciones.dat' using 1:2 with lines title 'f(x)', "); // Ingreso de f(x).
        fprintf(gnuplotPipe, "'funciones.dat' using 1:3 with lines title 'g(x)', "); // Ingreso de g(x).
        // Nota: Puede que parezca que ni siquiera hay curva de e(x), pero sí hay es que es diminuta por tan amplio dominio total,
        // si se desea se puede ampliar, cambiando xi y xf, y se observará que sí se genera, de igual forma por eso se hace la gráfica zoom.
        fprintf(gnuplotPipe, "'error.dat' using 1:2 with lines lw 2 lc 'red' title 'Error <= %.2f%%'\n", error_escogido); // Ingreso de e(x). 
        // Se insertan los comandos para concluir el código del gráfico:
        fprintf(gnuplotPipe, "exit\n");
        fflush(gnuplotPipe);
        pclose(gnuplotPipe); // Se cierra.
        // Mensajes informativos sobre creación del gráfico:
        printf("\nGráfico generado y guardado como 'plot.png', por favor buscarlo en su carpeta actual.\n");
    } else {
        printf("Se ha generado un error creando la gráfica 'plot.png'\n");
    }
    
    // Código de graficación #2: (Con zoom).
    gnuplotPipe = popen("gnuplot -persistent", "w"); // Se abre.
    if (gnuplotPipe != NULL) {
        // Configuraciones de principal interés para la gráfica de Zoom:
        fprintf(gnuplotPipe, "set terminal pngcairo size 800,600\n"); // Tamaño de imagen.
        fprintf(gnuplotPipe, "set output 'plot_zoom.png'\n"); // Nombre de imagen y formato.
        fprintf(gnuplotPipe, "set title 'Funciones Cuadráticas (Zoom)'\n"); // Título de la gráfica.
        fprintf(gnuplotPipe, "set xlabel 'Eje X'\n"); // Nombre del eje X.
        fprintf(gnuplotPipe, "set ylabel 'Eje Y'\n"); // Nombre del eje Y.
        fprintf(gnuplotPipe, "set xrange [-50:100]\n"); // Rango disminuido para el eje X.
        fprintf(gnuplotPipe, "set yrange [-50:400]\n"); // Rango disminuido para el eje Y.
        // Con esta línea se agrega el texto de los subdominios:
        fprintf(gnuplotPipe, "set label '%s' at graph 0.6, graph 0.05 left font ',9'\n", subdominios); // "graph" indica posición y ',9' el tamaño.
        // Con estas líneas se agregan las curvas f(x), g(x) y e(x) con sus leyendas:
        fprintf(gnuplotPipe, "plot 'funciones.dat' using 1:2 with lines title 'f(x)', "); // Ingreso de f(x).
        fprintf(gnuplotPipe, "'funciones.dat' using 1:3 with lines title 'g(x)', "); // Ingreso de g(x).
        fprintf(gnuplotPipe, "'error.dat' using 1:2 with lines lw 2 lc 'red' title 'Error <= %.2f%%'\n", error_escogido); // Ingreso de e(x). 
        // Se insertan los comandos para concluir el código del gráfico:
        fprintf(gnuplotPipe, "exit\n");
        fflush(gnuplotPipe);
        pclose(gnuplotPipe); // Se cierra.
        // Mensajes informativos sobre creación del gráfico zoom:
        printf("Gráfico con zoom generado y guardado como 'plot_zoom.png', por favor buscarlo en su carpeta actual.\n");
    } else {
        printf("Se ha generado un error creando la gráfica 'plot_zoom.png'\n");
    }
    // Final del código de graficación.
    printf("\n***** Fin del programa: Error Esperado *****\n\n");
    return 0; // Se concluye correctamente el programa.
}

// Bloque de funciones:
// Función para obtener f(x) con respecto a una x.
float funcion1(float *p, float x){
    return *p * x * x + *(p + 1) * x + *(p + 2); // Se accede a los primeros tres elementos a, b y c, con el puntero.
}

// Función para obtener g(x) con respecto a una x.
float funcion2(float *p, float x){
    return *(p + 3) * x * x + *(p + 4) * x + *(p + 5); // Se accede a los últimos tres elementos a, b y c, con el puntero.
}

// Función para obtener e(x), el porcentaje de error de la diferencia relativa entre ambas funciones, con respecto a una x.
float error_x(float f, float g){
    return 100 * fabsf((f - g) / f); // Se aplica el valor absoluto por la resta.
}
// Fin del código. Gracias.
