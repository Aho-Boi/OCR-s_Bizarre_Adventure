# EPITA Practical Programming S3 - 2016/2017
# Makefile
# Marwan Burelle
 
# Compilers and options
CC=gcc
CPPFLAGS= -MMD
CFLAGS= -Wall -Wextra -std=c99 -pedantic -O2 -Werror
LDFLAGS=
LDLIBS= -lm
 
SRC = main_neuron.c xor_func.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}
 
all: main
 
main: ${OBJ}
  
.PHONY: clean

clean:
	rm -f ${OBJ} ${DEP}
	rm -f main_neuron
 
-include ${DEP}
# END
