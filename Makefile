CC=gcc

CPPFLAGS= `pkg-config --cflags sdl`
CFLAGS= -Wall -Wextra -Werror -std=c99 -g
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image -lm

SRC=  detect_lines.c
OBJ= ${SRC:.c=.o}

all: detect_lines

main: ${OBJ}

clean:
	rm -f *~ *.o
	rm -f detect_lines
