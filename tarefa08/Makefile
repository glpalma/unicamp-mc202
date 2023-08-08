CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g

.PHONY: all clean

all: listas_legais

listas_legais: *.c
	gcc $(CFLAGS) -c arvore_listas_legais.c
	gcc $(CFLAGS) -c listas_legais.c
	gcc $(CFLAGS) -o listas_legais listas_legais.o arvore_listas_legais.o

clean:
	rm -f listas_legais
	rm -f *.o
