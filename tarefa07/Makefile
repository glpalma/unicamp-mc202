CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g

.PHONY: all clean

all: mensageiro

mensageiro: mensageiro.c
	gcc $(CFLAGS) -c arvore_tokens.c
	gcc $(CFLAGS) -c mensageiro.c
	gcc $(CFLAGS) -o mensageiro mensageiro.o arvore_tokens.o

clean:
	rm -f mensageiro
	rm -f *.o
