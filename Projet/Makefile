CC = gcc #On définit une variable  pour le compilateur
TARGET = math_suite
OBJ = src/main.o src/lib_utilitaires.o  src/lib_fonction_principale.o

math_suite: main.o lib_utilitaires.o lib_fonction_principale.o
	$(CC) -std=c99 -o math_suite src/main.o src/lib_utilitaires.o src/lib_fonction_principale.o

main.o : main.c include/lib_utilitaires.h include #Le -c indique qu'on veut compiler sans faire d'executable
	$(CC) -std=c99 -c  src/main.c  

lib_utilitaires.o : src/lib_utilitaires.c include/lib_utilitaires.h
	$(CC) -std=c99 -c src/lib_utilitaires.c

lib_fonction_principale.o : src/lib_fonction_principale.c include/lib_fonction_principale.h include/lib_utilitaires.h
	$(CC) -std=c99 -c src/lib_fonction_principale.c


clean:
	rm -f $(OBJ) $(TARGET)
