CC=gcc
CFLAGS=-g -std=c89

all: main run

main: main.c
	${CC} main.c ${CFLAGS} -o main

run:
	./main > image.ppm

view:
	nomacs image.ppm 2> /dev/null

clean:
	rm main

