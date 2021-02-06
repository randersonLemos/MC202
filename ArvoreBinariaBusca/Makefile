CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: TestaArvBinBusca

TestaArvBinBusca: TestaArvBinBusca.c
	gcc $(CFLAGS) -Wno-unused-variable -c ArvBinBusca.c $(LDFLAGS)
	gcc $(CFLAGS) -Wno-unused-variable -c TestaArvBinBusca.c $(LDFLAGS)
	gcc $(CFLAGS) -Wno-unused-variable -o TestaArvBinBusca ArvBinBusca.o TestaArvBinBusca.o $(LDFLAGS)

clean:
	rm -f TestaArvBinBusca
	rm -f *.o
