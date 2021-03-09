#include <stdio.h>
#include "fifo.h"
#include "estruturas.h"

Fila* fifo_execucao(int tamanho_tabela, int pagina_acesso, unsigned int endereco, char operacao, int *paginas_lidas, int *paginas_escritas)
{
    Fila *fila;

    if ((fila = (Fila *) malloc(sizeof(Fila))) == NULL)           
    {
        printf("Erro: Fila fifo não criada\n");
        exit(1);
    }

    fila->inicio = NULL;         
    fila->fim = NULL;         
    fila->tamanho = 0;    
    
    Item* item;
    item = fila->inicio;
    int pagina_fila = 0;

    while(item != NULL)
    {      
      if(item->pagina.numero == pagina_acesso)
      { 
        *paginas_escritas += 1;               
        item->pagina.endereco_acessado = endereco;
        item->pagina.bit_controle = operacao == 'W';
        pagina_fila = 1;
        break;
      }

      item = item->proximo;
    }
    
    if(pagina_fila == 0)
    { 
      *paginas_lidas += 1;      
      Pagina* pagina = (Pagina*) malloc(sizeof(Pagina));
      if (pagina == NULL)           
      {
          printf("Erro: Pagina não criada\n");
          exit(1);
      }

      pagina->numero = pagina_acesso;    
      pagina->bit_controle = operacao == 'W';
      pagina->endereco_acessado = endereco;
      adicionarItemFila(fila, fila->fim, *pagina);      
    }  

    return fila;
}

void fifo_listagem(Fila* fila)
{
  Item* item;
  item = fila->inicio;

  while(item != NULL)
  {      
      if(item->pagina.numero != 0 && item->pagina.endereco_acessado != 0)

      printf("     Pagina: %u - Endereço: %u - Bit de controle (Sim ou não): %s\n", item->pagina.numero, item->pagina.endereco_acessado, item->pagina.bit_controle ? "Sim" : "Não");      
      item = item->proximo;
  }
}