#include "estruturas.h"

Tabela analisarPaginaForaTabela(Tabela tabela, ItemMemoria* itens_memoria, int *paginas_lidas, int tamanho_tabela, int pagina_acesso, unsigned int endereco, char operacao);

Tabela segundachance_execucao(int tamanho_tabela, int pagina_acesso, unsigned int endereco, char operacao, int clock_cont, int *paginas_lidas, int *paginas_escritas);

void segundachance_listagem(Tabela tabela, int tamanho_tabela);