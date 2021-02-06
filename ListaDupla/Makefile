CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: testa_lista_dupla

testa_lista_dupla: testa_lista_dupla.c
	gcc $(CFLAGS) testa_lista_dupla.c lista_dupla.c -o testa_lista_dupla $(LDFLAGS)

clean:
	rm -f testa_lista_dupla
