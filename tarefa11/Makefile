CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: caminho

caminho: *.c
	gcc $(CFLAGS) -c raid_lugia.c $(LDFLAGS)
	gcc $(CFLAGS) -c caminho.c $(LDFLAGS)
	gcc $(CFLAGS) -o caminho caminho.o raid_lugia.o $(LDFLAGS)

clean:
	rm -f caminho
	rm -f *.o
