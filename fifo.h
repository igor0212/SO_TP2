#include "estruturas.h"

void fifo_execucao(int total_paginas, int numero_pagina_acessada, int hit, unsigned int endereco, char operacao, int contador_clock, int miss, Quadro *quadros_memoria, int escritas);

void fifo_listagem();