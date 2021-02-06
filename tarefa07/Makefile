CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
CFLAGS = -std=c99 -Wall
LDFLAGS = -lm

.PHONY: all clean

all: mensageiro

mensageiro: mensageiro.c
	gcc $(CFLAGS) -c ArvBinBusca.c $(LDFLAGS)
	gcc $(CFLAGS) -c mensageiro.c $(LDFLAGS)
	gcc $(CFLAGS) -o mensageiro ArvBinBusca.o mensageiro.o $(LDFLAGS)

clean:
	rm -f mensageiro
	rm -f *.o
