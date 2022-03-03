# Proyecto_en_C
Proyecto en lenguaje C realizado para el curso Programación Bajo Pataformas Abiertas III ciclo 2021.

Marianne Escalante B72710
Luis Diego Madrigal B94453
Katherine Vargas B88198

Bibliotecas necesarias:
GTK +3.0: se instala con:
$ sudo apt-get install libgtk-3-dev

Así también para poder compilar se necesitará tener instalado: 
$ sudo apt-get install pkg-config
$ sudo apt install gcc
$ sudo apt-get install make

Para compilar el código: 
En la terminal se debe de ubicar en la direccion respectiva donde se encuentre el $ archivo .c
Se debe tener descargado en archivo del make file: el cual se lee ingresando a la terminal $ make
donde aparecerá lo siguiente: 
gcc `pkg-config --cflags gtk+-3.0` -g -o gato proyecto_gato.c `pkg-config --libs gtk+-3.0`

y se ejcuta con:
./gato
