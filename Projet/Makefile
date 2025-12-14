CC = gcc #On définit une variable 


TARGET = math_suite
OBJ = src/main.o src/lib_tableaux_dynamiques.o 

math_suite: main.o lib_tableaux_dynamiques.o
	$(CC) -std=c99 -o math_suite src/main.o src/lib_tableaux_dynamiques.o

main.o : main.c include/lib_tableaux_dynamiques.h
	$(CC) -std=c99 -c  src/main.c 

lib_tableaux_dynamiques.o : src/lib_tableaux_dynamiques.c include/lib_tableaux_dynamiques.h
	$(CC) -std=c99 -c src/lib_tableaux_dynamiques.c


clean:
	rm -f $(OBJ) $(TARGET)
