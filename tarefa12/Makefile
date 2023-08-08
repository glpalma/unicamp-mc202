CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g

.PHONY: all clean

all: editor

editor: *.c
	gcc $(CFLAGS) -c planilha.c
	gcc $(CFLAGS) -c editor.c
	gcc $(CFLAGS) -o editor editor.o planilha.o

clean:
	rm -f editor
	rm -f *.o
