all: math_suite

math_suite: math_suite.c
	gcc -o math_suite math_suite.c -Wall

clean:
	rm -rf *.o

mrproper: clean
	rm -rf math_suite

