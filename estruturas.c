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
  item_novo->pagina.identificador = pagina.identificador;
  item_novo->pagina.ultimo_endereco_acessado = pagina.ultimo_endereco_acessado;
  item_novo->pagina.bit_controle = pagina.bit_controle;
          
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