CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: caminho

caminho: TestGrafo.c
	gcc $(CFLAGS) *.c -o TestGrafo $(LDFLAGS)

clean:
	rm -f caminho
