# EPITA Practical Programming S3 - 2016/2017
# Makefile
# Marwan Burelle
 
# Compilers and options
CC=gcc -rdynamic
CPPFLAGS= -MMD `pkg-config --cflags sdl` `pkg-config --cflags gtk+-3.0`
CFLAGS= -rdynamic -Wall -rdynamic -Wextra -rdynamic -std=c99 -rdynamic -pedantic -O0 -g -rdynamic
LDFLAGS=
LDLIBS= -lm `pkg-config --libs sdl` -lSDL_image `pkg-config --libs gtk+-3.0`
 
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
