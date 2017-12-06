# Makefile
 
CC=gcc -fsanitize=address
CPPFLAGS= -MMD -D_XOPEN_SOURCE=500
CFLAGS= -Wall -Wextra -std=c99 -O2
LDFLAGS=
LDLIBS= -lm
 
# you should at least create empty file insert_sort.c and quick_sort.c in
# order to compile
 
SRC= file_func.c mat_func.c ocr_func.c main_func.c main.c
OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}
 
all: main
 
-include ${DEP}
 
main: ${OBJ}
 
clean:
	rm -f ${OBJ} ${DEP} main
 
# END
