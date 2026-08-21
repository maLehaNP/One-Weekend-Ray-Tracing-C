CC = gcc
CFLAGS = -g -std=c89 -I include#-O3 -flto
LDFLAGS = -lm
SOURCES = src/main.c
HEADERS = include/vec3.h include/color.h

all: main

main: ${SOURCES} ${HEADERS}
	${CC} ${SOURCES} ${CFLAGS} ${LDFLAGS} -o $@

run:
	./main > image.ppm

view:
	nomacs image.ppm 2> /dev/null

clean:
	rm main

