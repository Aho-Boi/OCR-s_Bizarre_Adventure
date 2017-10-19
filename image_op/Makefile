## Makefile
 
CC=gcc
 
CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image

SRC= load_picture.c pixel_color.c images_operations.c main.c 
OBJ= ${SRC:.c=.o}
DEP= ${SRC:.o=.d}
 
all: main
 
main: ${OBJ}
 
clean:
	${RM} ${OBJ} ${DEP} main
 
-include ${DEP}
 
# END
