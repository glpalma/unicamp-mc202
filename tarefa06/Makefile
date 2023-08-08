CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: sala_de_espera

sala_de_espera: sala_de_espera.c
	gcc $(CFLAGS) -c lista_ligada.c
	gcc $(CFLAGS) -c adm_hospitalar.c
	gcc $(CFLAGS) -c sala_de_espera.c
	gcc $(CFLAGS) -o sala_de_espera sala_de_espera.o lista_ligada.o adm_hospitalar.o


clean:
	rm -f sala_de_espera
	rm -f *.o
