#include "estruturas.h"

Tabela doisa_execucao(int total_paginas, int numero_pagina_acessada, int hit,  unsigned int endereco, char operacao, int contador_clock, int miss, Quadro *quadros_memoria, int escritas);

void doisa_listagem(Tabela tabela, int tamanho_tabela);