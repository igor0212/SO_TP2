#include "estruturas.h"

void lru_execucao(int total_paginas, Tabela tabela_nao_fifo, int numero_pagina_acessada,  unsigned int endereco, char operacao, int contador_clock, Quadro *quadros_memoria, int *paginas_lidas, int *paginas_escritas);
void lru_listagem(int tamanho_tabela, Tabela tabela_nao_fifo);