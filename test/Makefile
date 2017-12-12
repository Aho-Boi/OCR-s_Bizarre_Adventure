## Makefile for the OCR

## Compilers vars

CC			= gcc 
CPPFLAGS= -MMD `pkg-config --cflags sdl` 
CFLAGS  = -Wall -Wextra -Werror -std=c99 -O2
LDFLAGS = 
LDLIBS	= `pkg-config --libs sdl` -lSDL_image -lm

OBJ = ${patsubst %.c, %.o,$(shell find . -name '*.c')}
DEP	= ${SRC:.o=.d}

RM = rm -rf
#BINARY = main

.PHONY: all clean

all: main

main: ${OBJ}

clean:
	${RM} ${OBJ} *~
	$(shell find . -type f -name '*.d' -exec rm {} +)
	${RM} main

-include ${DEP}

#END
