CC=mpicxx
CC1=gcc

all: pairwise bruck

pairwise:
	$(CC) pair_wise.cpp -o pair_wise.o
bruck:
	$(CC) bruck.cpp -o bruck.o
clean:
	rm -f pair_wise.o bruck.o