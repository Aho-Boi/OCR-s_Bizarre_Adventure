# EPITA Practical Programming S3 - 2016/2017
# Makefile
# Marwan Burelle
#gcc -Wall -Wextra -g gtk_OCR.c `pkg-config --cflags --libs gtk+-3.0` -rdynamic -o mainGlade
# Compilers and options
CC=gcc
CPPFLAGS= -MMD `pkg-config --cflags sdl` `pkg-config --cflags gtk+-3.0`
CFLAGS= -Wall -Wextra -std=c99 -pedantic -O0 -g -rdynamic
LDFLAGS=
LDLIBS= -lm `pkg-config --libs sdl` -lSDL_image `pkg-config --libs gtk+-3.0`
 
SRC = ../ocr/load_picture.c ../ocr/ogc_func.c ../ocr/my_string.c ../ocr/pixel_color.c ../defense/loadOcr.c ../defense/ocr.c gtk_OCR.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}
 
all: gtk_OCR
 
gtk_OCR: ${OBJ}
  
.PHONY: clean

clean:
	${RM} ${OBJ} ${DEP} gtk_OCR
 
-include ${DEP}
# END
