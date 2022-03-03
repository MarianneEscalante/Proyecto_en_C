all:
	gcc `pkg-config --cflags gtk+-3.0` -g -o gato proyecto_gato.c `pkg-config --libs gtk+-3.0`

