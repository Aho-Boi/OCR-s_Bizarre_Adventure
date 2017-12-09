# Makefile
 
GCC=gcc
CPPFLAGS= -MMD `pkg-config --cflags sdl` 
CFLAGS= -Wall -Wextra -std=c99 -O0 -g
LDFLAGS=
LDLIBS= -lm `pkg-config --libs sdl` -lSDL_image

SRC= my_string.c load_picture.c file_func.c mat_func.c ocr_func.c main_func.c math_func.c main.c
OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}
 
all: main
 
-include ${DEP}
 
main: ${OBJ}
 
clean:
	rm -f ${OBJ} ${DEP} main
 
# END
