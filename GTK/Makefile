## Simple SDL mini code

CC=gcc

CPPFLAGS= ${GTKCFLAGS}
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --cflags --libs gtk-2.0` 

OBJ= gtk_test.o
DEP= ${SRC:.o=.d}

all: main

main: ${OBJ}

clean:

-include ${DEP}

# END
