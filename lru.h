#include "estruturas.h"

void lru(int total_paginas, Tabela tabela_nao_fifo, int numero_pagina_acessada,  unsigned int endereco, char operacao, int contador_clock, Quadro *quadros_memoria);
void lru_listagem(int tamanho_tabela, Tabela tabela_nao_fifo);