CFLAGS=-Wall -g -I/usr/X11R6/include `pkg-config --cflags cairo`
LDFLAGS=-Wall -g `pkg-config --libs cairo` -L/usr/X11R6/lib -lX11 -lpng

all: bin/main

bin/main: bin/main.o bin/window.o bin/line.o bin/fade.o bin/heart.o bin/text.o
	cc -o bin/main ${LDFLAGS} $?

bin/%.o: %.c
	cc -o $@ ${CFLAGS} -c $<
