# EPITA Practical Programming S3 - 2016/2017
# Makefile
# Marwan Burelle
 
# Compilers and options
CC=gcc
CPPFLAGS= -MMD `pkg-config --cflags sdl` 
CFLAGS= -Wall -Wextra -std=c99 -pedantic -O0 -g
LDFLAGS=
LDLIBS= -lm `pkg-config --libs sdl` -lSDL_image
 
SRC = main_neuron.c ogc_func.c load_picture.c my_string.c pixel_color.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}
 
all: main_neuron
 
main_neuron: ${OBJ}
  
.PHONY: clean

clean:
	${RM} ${OBJ} ${DEP} main_neuron training
 
-include ${DEP}
# END
