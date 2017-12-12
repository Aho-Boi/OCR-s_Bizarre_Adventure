# EPITA Practical Programming S3 - 2016/2017
# Makefile
# Marwan Burelle
 
# Compilers and options
CC=gcc
CPPFLAGS= -MMD `pkg-config --cflags sdl` 
CFLAGS= -Wall -Wextra -std=c99 -pedantic -O0 -g
LDFLAGS=
LDLIBS= -lm `pkg-config --libs sdl` -lSDL_image
 
SRC = ../ocr/load_picture.c ../ocr/ogc_func.c ../ocr/my_string.c ../ocr/pixel_color.c loadOcr.c ocr.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}
 
all: ocr
 
ocr: ${OBJ}
  
.PHONY: clean

clean:
	${RM} ${OBJ} ${DEP} ocr
 
-include ${DEP}
# END
