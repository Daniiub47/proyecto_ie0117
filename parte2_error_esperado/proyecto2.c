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
//#include <string.h> // Esta es para manejo de strings.
//#include <stdlib.h> // Se utiliza para la función system.

// Definición de las funciones:
float funcion1(float *p, float x); // Función para obtener f(x) con respecto a una x.
float funcion2(float *p, float x); // Función para obtener g(x) con respecto a una x.
float error_x(float f, float g); // Función para encontrar el porcentaje de error de la diferencia relativa entre funciones con una x.

// Código main:
int main() {
    //*** CONFIGURACIONES ***
    
    // Se declara el dominio total a evaluar:
    int xi = -100000; // Valor del eje X inicial.
    int xf = 100000; // Valor del eje X final.
    
    // Se declara el valor de muestreo:
    float muestreo_x = 0.1; // Es el valor de aumento para obtener los múltiples resultados.
    
    //*** FIN DE CONFIGURACIONES ***

    // Declaración de variables:
    float a, b, c, d, e, f; // Constantes de las funciones.
    float array_cons[6]; // array que va a almacenar todas las constantes para un más fácil manejo.
    float *p_array = array_cons; // Un puntero al primer elemento del array de constantes.
    float error_escogido;

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
    
    // Bloque para almacenar las constantes en un solo array por medio del puntero:
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
    if (doc_funcs == NULL) {
        perror("\nError al abrir funciones.dat, necesario para almacenar los datos de las funciones.\n"); // Se imprime mensaje de error.
        return 1; // Se concluye el programa por error ya que return distinto de 0 es un error.
    }
    
    // Archivo con la información de la función de error:
    FILE *doc_error = fopen("error.dat", "w"); // Se crea el puntero *doc_error para acceder luego y se usa con escritura para crear y sobreescribir.
    if (doc_error == NULL) {
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
        fprintf(doc_funcs, "%f %f %f\n", x, fx, gx);
        // Se previene el caso en el que f(x) = 0 ya que podría generar una indeterminación:
        if (fx != 0) {
            float ex = error_x(fx, gx);
            // Se encuentran los valores de X que cumplan que ex sea menor o igual que el porcentaje de error del usuario:
            if (ex <= error_escogido) {
                fprintf(doc_error, "%f\n", x);
            }
        }
    }
    
    // Se cierran los archivos al finalizar.
    fclose(doc_funcs);
    fclose(doc_error);
    
    return 0;
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
    return 100 * fabsf((f - g) / f);
}

// código que puede ser útil que se usó para hacer pruebas pero ya no es necesario:

//printf("Resultados: %.3f - %.3f - %.3f - %.3f\n", f_x, g_x, e_x, error_escogido);
//printf("Constantes: %.3f - %.3f - %.3f - %.3f - %.3f - %.3f\n", *p_array, *(p_array + 1), array_cons[2], array_cons[3], array_cons[4], array_cons[5]);
/*// Obtención de f(x):
float fx = funcion1(p_array, 5);
// Obtención de g(x):
float gx = funcion2(p_array, 5);
// Obtención de e(x):
float ex = error_x(fx, gx);*/
