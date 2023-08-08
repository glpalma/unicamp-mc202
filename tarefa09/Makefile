CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: diadeuber

diadeuber: *.c
	gcc $(CFLAGS) -c adm_uber.c
	gcc $(CFLAGS) -c diadeuber.c
	gcc $(CFLAGS) -o diadeuber adm_uber.o diadeuber.o

clean:
	rm -f diadeuber
	rm -f *.o
