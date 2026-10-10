CC = gcc
CFLAGS = -std=c99 -I include -g -O3 -mavx2 -ffast-math#-fopenmp
LDFLAGS = -lm -static
SOURCES = src/main.c
HEADERS = include/vec3.h include/color.h include/ray.h

all: main

main: ${SOURCES} ${HEADERS}
	${CC} ${SOURCES} ${CFLAGS} ${LDFLAGS} -o $@

run:
	./main > image.ppm

view:
	nomacs image.ppm 2> /dev/null

clean:
	rm main

