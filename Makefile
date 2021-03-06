tp2virtual: main.o fifo.o lru.o doisa.o estruturas.o
	gcc main.o fifo.o lru.o doisa.o estruturas.o -o tp2virtual
	
main.o: main.c
	gcc -c -g main.c
	
fifo.o: fifo.c fifo.h
	gcc -c -g fifo.c

lru.o: lru.c lru.h
	gcc -c -g lru.c

doisa.o: doisa.c doisa.h
	gcc -c -g doisa.c

estruturas.o: estruturas.c estruturas.h
	gcc -c -g estruturas.c