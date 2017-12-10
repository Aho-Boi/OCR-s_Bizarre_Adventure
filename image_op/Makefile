## Makefile

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -std=c99 -O0 -g
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image


SRC=	  
OBJ= picture_operations.o load_picture.o pixel_color.o main.o
DEP= ${SRC:.o=.d}

all: main

main: ${OBJ}

clean:
  
	${RM} ${OBJ} ${DEP} main

-include ${DEP}

# END


