#include "estruturas.h"

Tabela media_execucao(int tamanho_tabela, int numero_pagina_acessada,  unsigned int endereco, char operacao, int contador_clock, int *paginas_lidas, int *paginas_escritas);
void media_listagem(Tabela tabela, int tamanho_tabela);   