#include "estruturas.h"

#pragma once

void lru(int total_paginas, tabela tabela_nao_fifo, int numero_pagina_acessada, int hit,  unsigned int endereco, char operacao, int contador_clock, int miss, quadro *quadros_memoria, int escritas);