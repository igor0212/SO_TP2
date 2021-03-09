#include "estruturas.h"

void adicionarItemFila(Fila *fila, Item *item, Pagina pagina)
{         
  Item *item_novo;         

  if ((item_novo = (Item *) malloc (sizeof (Item))) == NULL)
  {
    printf("Erro: Item novo não criada\n");
    exit(1);
  }          

  item_novo->pagina.numero = pagina.numero;
  item_novo->pagina.id = pagina.id;
  item_novo->pagina.endereco_acessado = pagina.endereco_acessado;
  item_novo->pagina.suja = pagina.suja;
          
  if(item == NULL)
  {           
    if(fila->tamanho == 0)     
    {
      fila->fim = item_novo;               
    }        
    
    item_novo->proximo = fila->inicio;           
    fila-> inicio = item_novo;         
  }
  else 
  {           
    if(item->proximo == NULL)
    {
      fila->fim = item_novo;           
    }

    item_novo->proximo = item->proximo;           
    item-> proximo = item_novo;         
  }         

  fila->tamanho++;           
}