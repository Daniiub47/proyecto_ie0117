/*
*******************************************************
*** Universidad de Costa Rica                       ***
*** Programación Bajo Plataformas Abiertas - IE0117 ***
*** Fecha: 27 de junio del 2024                     ***
*** Creador: Carlos Andrés Garreta Quesada - C13120 ***
*******************************************************

*** Proyecto Primera Parte: Tic Tac Toe ***

Descripción: Esta parte del código corresponde al primer problema presentado en 
el proyecto final. En esta ocación se debe realizar un juego de gato con interface 
gráfica (gtk/glade), en donde se presentará primeramente una matriz 3x3 con 9 botones 
interactivos. Se debe verificar el gane y el empate de los jugadores "X" y "O" de tal 
forma que se imprima en la misma interface el ganador al igual que si hay un empate.

*/




// Incluimos las librerias que se van a usar 
#include <gtk/gtk.h> // Librería gtk3 

GtkWidget *window; // Representa la ventana del juego 
GtkWidget *grid; // Representa la cuadrícula donde estarán los botones
GtkWidget *buttons[3][3]; // Representa los 9 botones de la matríz 3x3 
GtkWidget *label; // Este Widget permite mostrar el estado del juego (proporciona texto)
gboolean turno_jugador = TRUE;  // Variable booleana que indica el turno del jugador (TRUE=X, FALSE=O)
gboolean fin_del_juego = FALSE; // Variable booleana que indica el estado del juego

// Función para verificar si hay un ganador
static gboolean verificar_ganador() { // Función que retorna el ganador
    const gchar *tablero[3][3]; // Representa el estado actual del tablero
    // bucles anidados para recorrer todos los botones 
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) { 
            tablero[i][j] = gtk_button_get_label(GTK_BUTTON(buttons[i][j])); // Se obtiene el texto actual del boton y se guarda en "tablero"
        }
    }
    
    // Bucle para verificar las filas y columnas 
    for (int i = 0; i < 3; i++) { 
    // Se comparan los strings comprobando que los tres elementos de la fila o columna son iguales o estan vacíos 
        if (g_strcmp0(tablero[i][0], tablero[i][1]) == 0 && g_strcmp0(tablero[i][0], tablero[i][2]) == 0 && g_strcmp0(tablero[i][0], "") != 0) { // g_strcmp0 es una función de comparación de cadenas 
            return TRUE;  // Verifica la fila ganadora
        }
        if (g_strcmp0(tablero[0][i], tablero[1][i]) == 0 && g_strcmp0(tablero[0][i], tablero[2][i]) == 0 && g_strcmp0(tablero[0][i], "") != 0) {
            return TRUE;  // Verifica la columna ganadora 

    
        }
    }
    
    // Se verifica si gana de forma diagonal de forma similar a como se hizo en las filas y columnas 
    if (g_strcmp0(tablero[0][0], tablero[1][1]) == 0 && g_strcmp0(tablero[0][0], tablero[2][2]) == 0 && g_strcmp0(tablero[0][0], "") != 0) {
        return TRUE;  // Primera Diagonal 
    }
    if (g_strcmp0(tablero[0][2], tablero[1][1]) == 0 && g_strcmp0(tablero[0][2], tablero[2][0]) == 0 && g_strcmp0(tablero[0][2], "") != 0) {
        return TRUE;  // Segunda diagonal 
    }
    
    return FALSE;  // Si no hay ganador se retoma el FALSE
}

// Función para verificar si hay un empate
static gboolean verificar_empate() {
    // Bucles anidados para recorrer todos los botones
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (g_strcmp0(gtk_button_get_label(GTK_BUTTON(buttons[i][j])), "") == 0) { // Verifica si los botones están vacios (FALSE = 0, TRUE = 1)
                return FALSE;  // Retorna FALSE si todavía hay espacios 
            }
        }
    }
    return TRUE;  // Retorna FALSE si no hay espacios por ende sería empate 
}


// Función llamada cada vez que se interactua con un botón 
static void boton_interactivo(GtkWidget *widget, gpointer data) { 
    // Verifica si el juego ya terminó 
    if (fin_del_juego) {
        return;  // Si el juego termina no hace nada
    }

    // Verifica si el botón ya tiene un label 
    const gchar *current_label = gtk_button_get_label(GTK_BUTTON(widget));
    if (g_strcmp0(current_label, "") != 0) { // Si el botón ya tiene una label no se hace nada
        return;
    }
    
    // Marca una "O" o "X" dependiendo del turno actual 
    if (turno_jugador) {
        gtk_button_set_label(GTK_BUTTON(widget), "X"); //Marca la "X"
    } else {
        gtk_button_set_label(GTK_BUTTON(widget), "O"); //Marca la "O"
    }
    
    // Verifica el ganador
    if (verificar_ganador()) {
        gchar *winner = turno_jugador ? "X" : "O"; // Se usa un operador ternario (? :) para asignar el jugador correspondiente al ganador
        gchar *message = g_strdup_printf("¡El jugador %s ha ganado!", winner); // Mensaje del ganador
        gtk_label_set_text(GTK_LABEL(label), message); // Actualiza el texto en la interfaz gráfica
        g_free(message); // Libera memoria
        fin_del_juego = TRUE; // Fin del juego 
        return;
    }
    
    // Verificar el empate
    if (verificar_empate()) {
        gtk_label_set_text(GTK_LABEL(label), "¡Empate!"); // Actualiza el texto en la interfaz gráfica 
        fin_del_juego = TRUE; // Finaliza el juego 
        return;
    }
    
    // Cambiar el turno
    turno_jugador = !turno_jugador;
    gtk_label_set_text(GTK_LABEL(label), turno_jugador ? "Juega: X" : "Juega: O"); // Mientras continúe el juego cambia el turno del jugador y lo muestra en la interfaz 
}

// Función que activa la app de GTK 
static void activate(GtkApplication *app, gpointer user_data) {
    // Crear la ventana principal
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Tic Tac Toe"); // Se establece el nombre de la app
    gtk_container_set_border_width(GTK_CONTAINER(window), 10); // Crea un borde de 10 pixeles

    // Crear un contenedor de cuadrícula y la añade a la ventana principal
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Crear los botones del tablero
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            buttons[i][j] = gtk_button_new_with_label(""); // Crea un tablero con los 9 botones
            gtk_widget_set_size_request(buttons[i][j], 100, 100); // Se les da un tamaño de 100x100 pixeles 
            g_signal_connect(buttons[i][j], "clicked", G_CALLBACK(boton_interactivo), NULL); // Se conecta a la funcion para interactuar con los botones 
            gtk_grid_attach(GTK_GRID(grid), buttons[i][j], i, j, 1, 1); // Añade los botones
        }
    }

    // Muestra el estado del juego por medio de un label 
    label = gtk_label_new("Empieza: X"); // label inicial el cual irá cambiando a lo largo del juego 
    gtk_grid_attach(GTK_GRID(grid), label, 0, 3, 3, 1); //añade el label a la cuadrícula 

    gtk_widget_show_all(window); // Muestra todos los widgets
}

// Función principal del programa 
int main(int argc, char **argv) { // argc = número de punteros , argv = array de strings (contiene los argumentos) 
    GtkApplication *app; // app = puntero a la aplicación GTK
    int status; // el status va a almacenar el códigode salida de la app

    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE); // Crea la aplicación GTK con el primer argumento siendo la ID de la app
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL); // Conecta la señal activate 
    status = g_application_run(G_APPLICATION(app), argc, argv); // Inica la ejecución de la app GTK pasando los comandos a la aplicación y almacenandolos en status
    g_object_unref(app); // Libera memoria

    return status; // Retorna el estado 
}
