CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g

.PHONY: all clean

all: calculadora

calculadora: calculadora.c
	gcc $(CFLAGS) -c inteiros_grandes.c
	gcc $(CFLAGS) -c calculadora.c
	gcc $(CFLAGS) -o calculadora calculadora.o inteiros_grandes.o

clean:
	rm -f calculadora
	rm -f *.o
