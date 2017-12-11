## OCR
 
CC=gcc
 
CPPFLAGS= `pkg-config --cflags 
CFLAGS= -Wall -Wextra -rdynamic
LDFLAGS=
LDLIBS= `pkg-config --libs gtk+-3.0`
 
OBJ= gtk_OCR.o
DEP= ${SRC:.o=.d}
 
all: gtk_OCR
 
main: ${OBJ}
 
clean:
	
 
-include ${DEP}
 
# END
