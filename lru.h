#include "estruturas.h"

Tabela lru_execucao(int tamanho_tabela, int numero_pagina_acessada,  unsigned int endereco, char operacao, int contador_clock, int *paginas_lidas, int *paginas_escritas);
void lru_listagem(Tabela tabela, int tamanho_tabela);   