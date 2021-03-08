#include <stdio.h>
#include "fifo.h"
#include "estruturas.h"

Fila* fifo_execucao(int tamanho_tabela, int pagina_acesso, unsigned int endereco, char operacao)
{
    Fila *fila;

    if ((fila = (Fila *) malloc(sizeof(Fila))) == NULL)           
    {
        printf("Erro: Fila fifo não criada\n");
        exit(1);
    }
    
    Item* item;
    item = fila->inicio;
    int pagina_fila = 0;

    while(item != NULL)
    {      
      if(item->pagina.numero == pagina_acesso)
      {        
        item->pagina.ultimo_endereco_acessado = endereco;
        item->pagina.suja = (operacao == 'W');
        pagina_fila = 1;
        break;
      }

      item = item->proximo;
    }
    
    if(!pagina_fila)
    {
      Pagina* pagina = (Pagina*) malloc(sizeof(Pagina));
      pagina->numero = pagina_acesso;    
      pagina->suja = (operacao == 'W');
      pagina->ultimo_endereco_acessado = endereco;
      inserir(fila, fila->fim, *pagina);
    }  

    return fila;
}

void fifo_listagem(Fila* fila)
{
  Item* item;
  item = fila->inicio;

  while(item != NULL)
  {      
      printf("Pagina: %u - Suja: %s - Ultimo endereco: %u\n", item->pagina.numero, item->pagina.suja ? "Sim" : "Não", item->pagina.ultimo_endereco_acessado);
      item = item->proximo;
  }
}