/* Proyecto en C: Juego gato
El proyecto es un  juego de gato presentado desde una interfaz gráfica,
que permite al usuario elegir la posición de los símbolos "O" u "X".
El código debe verificar si alguno de los jugadores ha completado una linea
vertical, diagonal u horizontal y  que de esta manera termine la partida.
Una vez colocado un simbolo en una casilla  no se pueden reemplazar*/

// Marianne Escalante B72710
// Luis Diego Madrigal B94453
// Katherine Vargas B88198

#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//Declaracion de funciones
void ganador_f();
void seleciona_ganador() ;
void click(GtkWidget *widget, gpointer data);
void activar(GtkApplication *aplicacion, gpointer userdata) ;

//Declaracion de variables globales
char jugador_actual = 'X';
int gameOver = 0;
int contador = 0;
GtkWidget *texto;
GtkWidget **botones;

int main(int argc, char *argv[]) {
//Declaracion de la clase GtkApplication
GtkApplication *aplicacion;
  int status;
  // gtk_application_new es una funcion de GtkApplication, con un id NULL
  //y sin flags
  aplicacion = gtk_application_new(NULL, G_APPLICATION_FLAGS_NONE);
  g_signal_connect(aplicacion, "activate", G_CALLBACK (activar), NULL);
  status = g_application_run(G_APPLICATION (aplicacion), argc, argv);
  g_object_unref(aplicacion);
  return status;
}

void activar(GtkApplication *app, gpointer userdata) {
GtkWidget *ventana;
ventana = gtk_application_window_new(app);

GtkWidget *tablero;
tablero = gtk_grid_new();

botones = (GtkWidget **)malloc(9*sizeof(GtkWidget *));

//Configura todos los botones para el juego de gato.
  for(int i=0; i<9; i++) {
    botones[i] = gtk_button_new();

//Si el lado izquierdo queda vacio, se retorna nulo porque causa problemas
//al momento de verificar la jugada.
gtk_button_set_label(GTK_BUTTON (botones[i]), " ");

//Configura la funcion del boton cuando es tocado.
g_signal_connect(botones[i], "clicked", G_CALLBACK (click), NULL);

//Hace que los botones se expandan y llenen todo el espacio de la ventana.
gtk_widget_set_hexpand(botones[i], TRUE);
gtk_widget_set_vexpand(botones[i], TRUE);


//Hace que la forma de los botones sea cuadrada.
gtk_grid_attach(GTK_GRID (tablero), botones[i], i/3, i%3, 1, 1);
    }

//Se encarga de que la X siempre vaya de primero.
texto = gtk_label_new("Jugador actual: X");
gtk_grid_attach(GTK_GRID (tablero), texto, 0, 3, 2, 1);

//Reinicia el juego cuando el boton de reinicio es utilizado.
gtk_container_add(GTK_CONTAINER (ventana), tablero);
gtk_widget_set_hexpand(tablero, TRUE);
gtk_widget_set_vexpand(tablero, TRUE);


//Muestra la ventana del juego.
gtk_window_set_title(GTK_WINDOW (ventana), "GATO");
gtk_window_set_default_size(GTK_WINDOW (ventana), 400, 400);
gtk_widget_show_all(ventana);
gtk_window_set_resizable(GTK_WINDOW(ventana),FALSE);
}

void ganador_f() {
  char cadena[10];
    sprintf(cadena, "%c GANA!", jugador_actual);
    gtk_label_set_text(GTK_LABEL (texto), cadena);
    gameOver = 1;
}

//Esta seccion se encarga de mostrar el jugador que acaba de jugar.
void seleciona_ganador() {
  char *simbolo;
    if(jugador_actual == 'X') simbolo = "X";
      else simbolo = "O";

  //Comando para el correcto funcionamiento de las filas.
  for(int i=0; i<3; i++) {
    int ganador = 1;
    for(int j=0; j<3; j++) {
      if(strcmp(gtk_button_get_label(GTK_BUTTON (botones[(3*i)+j])), simbolo)) ganador = 0;
    }
    if(ganador) {
      ganador_f();
      return;
    }
  }

  //Comando para el correcto funcionamiento de las columnas.
  for(int i=0; i<3; i++) {
    int ganador = 1;
    for(int j=0; j<3; j++) {
        if(strcmp(gtk_button_get_label(GTK_BUTTON (botones[(3*j)+i])), simbolo)) ganador = 0;
    }
    if(ganador) {
      ganador_f();
      return;
    }
  }

//Este condicional determina cuando el resultado de una partida es una
//diagonal derecha en el gato.
  if(!strcmp(gtk_button_get_label(GTK_BUTTON (botones[2])), simbolo) &&
      !strcmp(gtk_button_get_label(GTK_BUTTON (botones[4])), simbolo) &&
      !strcmp(gtk_button_get_label(GTK_BUTTON (botones[6])), simbolo)) {
    ganador_f();
    return;
  }

//Este condicional determina cuando el resultado de una partida es una
//diagonal izquierda en el gato.
  if(!strcmp(gtk_button_get_label(GTK_BUTTON (botones[0])), simbolo) &&
      !strcmp(gtk_button_get_label(GTK_BUTTON (botones[4])), simbolo) &&
      !strcmp(gtk_button_get_label(GTK_BUTTON (botones[8])), simbolo)) {
    ganador_f();
    return;
  }
}

//Se hace uso de esta funcion cuando uno de los botones se toca.
 void click(GtkWidget *widget, gpointer data) {
//Se asegura de que el boton tocado y no haya sido utilizado anteriormente.
  if(!strcmp(gtk_button_get_label(GTK_BUTTON (widget)), " ") && !gameOver) {

//Configura el cuadro de texto para el jugador actual.
char jugador_str [2];
    sprintf(jugador_str, "%c", jugador_actual);
    gtk_button_set_label(GTK_BUTTON (widget), jugador_str);

//Tambien, configura el cuadro de texto para el jugador actual.
char texto_str [18];
    sprintf(texto_str, "Jugador actual: %c", jugador_actual);
    gtk_label_set_text(GTK_LABEL (texto), texto_str);

    contador++;
    seleciona_ganador();
    jugador_actual = (jugador_actual == 'X') ? 'O' : 'X';
  }

  if(contador >= 9) {
    gtk_label_set_text(GTK_LABEL (texto), "Empate");
    gameOver = 1;
  }
}
