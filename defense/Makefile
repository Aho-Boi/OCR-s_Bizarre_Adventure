## OCR
 
#gtk_OCR: 
#	gcc -Wall -Wextra -g gtk_OCR.c `pkg-config --cflags --libs gtk+-3.0` -rdynamic -o mainGTK

#
# Variables:
#
CC = gcc
BIN = mainGtk
SRC = gtk_OCR.c
OBJ = gtk_OCR.o
 
 
#
# Flags d'erreurs:
#
 
 
#
# Flags pour le compilateur:
# 
CFLAGS = `pkg-config --cflags gtk+-3.0` -Wall -Wextra -rdynamic
 
 
#
# Flags pour l'editeur de liens:
#
 
LDFLAGS = `pkg-config --libs gtk+-3.0`
 
 
#
# Construction du programme:
#
all: $(BIN)
 
$(BIN): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) $(LDFLAGS) -o $(BIN) $(OBJ)
 
 
#
# Nettoyage:
#
clean:
	rm -f *.o *~ core $(BIN)
