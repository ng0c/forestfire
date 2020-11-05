CC=gcc
#CFLAGS=-Wall -Wextra -pedantic -std=c90 -O3
CFLAGS=-Wall -Wextra -pedantic -std=c90 -g3 -fsanitize=undefined -fsanitize=address
LDLIBS= -lm

demo_neillsimplescreen : neillsimplescreen.c neillsimplescreen.h forest.c
	$(CC) forest.c neillsimplescreen.c -o forest $(CFLAGS) $(LDLIBS)
