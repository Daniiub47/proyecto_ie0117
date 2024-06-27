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
//#include <math.h> // Esta es para las operaciones matemáticas.
//#include <string.h> // Esta es para manejo de strings.
//#include <stdlib.h> // Se utiliza para la función system.

// Definición de las funciones:

// Código main:
int main() {
    // Declaración de variables:
    float a, b, c, d, e, f; // Constantes de las funciones.
    float array_cons[6]; // array que va a almacenar todas las constantes para un más fácil manejo.
    float *p_array = array_cons; // Un puntero al primer elemento del array de constantes.

    // Se generan los mensajes hacia el usuario:
    printf("\n***** Bienvenido al programa: Error Esperado *****\n\n");
    printf("En este programa se mostrará el o los subdominios donde la diferencia de dos curvas cuadráticas sea menor al error escogido.\n");
    
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
    printf("La segunda función f(x) tiene la forma: d * x^2 + e * x + f\n");
    printf("Por favor agregue la constante d: ");
    scanf("%f", &d);
    printf("Por favor agregue la constante e: ");
    scanf("%f", &e);
    printf("Por favor agregue la constante f: ");
    scanf("%f", &f);
    
    // Bloque para almacenar las constantes en un solo array por medio del puntero:
    *p_array = a;
    *(p_array + 1) = b;
    *(p_array + 2) = c;
    *(p_array + 3) = d;
    *(p_array + 4) = e;
    *(p_array + 5) = f;
    
    printf("Constantes: %.3f - %.3f - %.3f - %.3f - %.3f - %.3f\n", array_cons[0], array_cons[1], array_cons[2], array_cons[3], array_cons[4], array_cons[5]);
    return 0;
}

// Bloque de funciones:
