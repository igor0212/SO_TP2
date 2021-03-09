#include "estruturas.h"

Fila* fifo_execucao(int tamanho_tabela, int pagina_acesso, unsigned int endereco, char operacao, int *paginas_lidas, int *paginas_escritas);

void fifo_listagem(Fila* fila);