tp2virtual: main.o fifo.o lru.o segundachance.o estruturas.o media.o comum.o
	gcc main.o fifo.o lru.o segundachance.o estruturas.o media.o comum.o -o tp2virtual
	
main.o: main.c
	gcc -c -g main.c
	
fifo.o: fifo.c fifo.h
	gcc -c -g fifo.c

lru.o: lru.c lru.h
	gcc -c -g lru.c

segundachance.o: segundachance.c segundachance.h
	gcc -c -g segundachance.c

media.o: media.c media.h
	gcc -c -g media.c

estruturas.o: estruturas.c estruturas.h
	gcc -c -g estruturas.c

comum.o: comum.c comum.h
	gcc -c -g comum.c