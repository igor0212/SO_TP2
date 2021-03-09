tp2virtual: main.o fifo.o lru.o segundachance.o estruturas.o
	gcc main.o fifo.o lru.o segundachance.o estruturas.o -o tp2virtual
	
main.o: main.c
	gcc -c -g main.c
	
fifo.o: fifo.c fifo.h
	gcc -c -g fifo.c

lru.o: lru.c lru.h
	gcc -c -g lru.c

segundachance.o: segundachance.c segundachance.h
	gcc -c -g segundachance.c

estruturas.o: estruturas.c estruturas.h
	gcc -c -g estruturas.c