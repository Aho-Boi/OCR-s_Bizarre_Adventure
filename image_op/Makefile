## Simple SDL mini code
 
CC=gcc
 
CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image
 
OBJ= load_picture.o pixel_color.o main.o
DEP= ${SRC:.o=.d}
 
all: main
 
main: ${OBJ}
 
clean:
	${RM} main
 
-include ${DEP}
 
# END
