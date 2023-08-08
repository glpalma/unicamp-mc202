CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all

all: 1c 2

2: 2.c
	gcc $(CFLAGS) 2.c -o 2 $(LDFLAGS)

1c: 1c.c
	gcc $(CFLAGS) 1c.c -o 1c $(LDFLAGS)
