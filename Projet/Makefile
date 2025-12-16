CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Iinclude

TARGET = math_suite
OBJ = src/main.o src/lib_utilitaires.o src/lib_fonction_principale.o

math_suite: src/main.o src/lib_utilitaires.o src/lib_fonction_principale.o
	$(CC) $(CFLAGS) -o math_suite src/main.o src/lib_utilitaires.o src/lib_fonction_principale.o


src/main.o: src/main.c include/lib_fonction_principale.h include/lib_utilitaires.h
	$(CC) $(CFLAGS) -c src/main.c -o src/main.o


src/lib_utilitaires.o: src/lib_utilitaires.c include/lib_utilitaires.h
	$(CC) $(CFLAGS) -c src/lib_utilitaires.c -o src/lib_utilitaires.o


src/lib_fonction_principale.o: src/lib_fonction_principale.c include/lib_fonction_principale.h include/lib_utilitaires.h
	$(CC) $(CFLAGS) -c src/lib_fonction_principale.c -o src/lib_fonction_principale.o


clean:
	rm -f src/main.o src/lib_utilitaires.o src/lib_fonction_principale.o math_suite

