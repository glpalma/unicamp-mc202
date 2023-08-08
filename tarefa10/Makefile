CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
# LDFLAGS = -lm

.PHONY: all clean

all: corretor

corretor: *.c
	gcc $(CFLAGS) -c dicionario.c
	gcc $(CFLAGS) -c corretor.c
	gcc $(CFLAGS) -o corretor dicionario.o corretor.o

clean:
	rm -f corretor
	rm -f *.o
