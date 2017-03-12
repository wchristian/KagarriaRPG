all: source game

source:
	gcc -c sources.c -lncurses

game:
	gcc -o game main.c sources.o -lncurses
