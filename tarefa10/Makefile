CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: corretor

corretor: corretor.c
	gcc $(CFLAGS) corretor.c Hash.c -o corretor $(LDFLAGS)

clean:
	rm -f corretor
