CC=gcc
AR=ar
CFLAGS=-g -Wall -W -I/usr/include/SDL -lpthread -lSDL 
SRC=fractal.c tools.c
OBJ=$(SRC:.c=.o)
LIBFILE=libfractal.a


all: main

main: main.c  lib
	gcc -o main  main.c  libfractal/fractal.h -Ilibfractal/ $(CFLAGS)

lib:
	cd libfractal && $(MAKE) 

clean:	
		rm -rf main
		rm -rf *.o
		rm -rf libfractal/*.o
		rm -rf libfractal/*.a
